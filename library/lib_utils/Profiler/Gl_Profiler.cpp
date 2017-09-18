#include "Profiler.h"


#include <lib_utils/GenericMsg/GenericMsg.h>
#include <lib_utils/UniStream/UniStream.h>
#include <lib_utils/Network/Messengers/Messenger.h>
#include <lib_utils/UniObject/UniMsg.h>
#include <chrono>
#include "Gl_Profiler.h"
#include <GL/glu.h>


//#define EGT_GPU_PROFILING_ON

namespace GlProfilerInternals
{
    static GLProfilerContext s_mainProfiler;
    static std::mutex s_mainCustomLocker;
    static std::map<int, GLProfilerContext> s_customProfiles;
    static std::atomic_bool s_isCustomProfilingOn = {false};
}

namespace egt
{


template<>
egt::oUniStream& operator<< (egt::oUniStream& out, const TextureMonitoring& info)
{
    out << info.hasGameId << info.hasImageName << info.hasAllocatorName << info.hasWidth << info.hasHeight << info.hasPixelSize;
    out << info.gameId << info.imageName << info.allocatorName << info.width << info.height << info.pixelSize;
    out << info.status << info.bindCount;



    int64_t generatedTime = std::chrono::duration_cast<std::chrono::milliseconds>(info.generatedTime.time_since_epoch()).count();
    int64_t lastBindTime = std::chrono::duration_cast<std::chrono::milliseconds>(info.lastBindTime.time_since_epoch()).count();
    int64_t uploadedTime = std::chrono::duration_cast<std::chrono::milliseconds>(info.uploadedTime.time_since_epoch()).count();

    out << generatedTime
        << lastBindTime
        << uploadedTime;

    return out;
}

///////////////////////////////////////////////////////////////////////////
template<>
egt::iUniStream& operator>> (egt::iUniStream& in, TextureMonitoring& info)
{
    in >> info.hasGameId >> info.hasImageName >> info.hasAllocatorName >> info.hasWidth >> info.hasHeight >> info.hasPixelSize;
    in >> info.gameId >> info.imageName >> info.allocatorName >> info.width >> info.height >> info.pixelSize;
    in >> info.status >> info.bindCount;
    int64_t generatedTime = 0;
    int64_t lastBindTime = 0;
    int64_t uploadedTime = 0;

    in >> generatedTime
        >> lastBindTime
        >> uploadedTime;

    auto generatedTimeMs = std::chrono::steady_clock::time_point(std::chrono::milliseconds(generatedTime));
    auto lastBindTimeMs =std::chrono::steady_clock::time_point(std::chrono::milliseconds(lastBindTime));
    auto uploadedTimeMs = std::chrono::steady_clock::time_point(std::chrono::milliseconds(uploadedTime));

    info.generatedTime = std::chrono::time_point_cast<std::chrono::milliseconds>(generatedTimeMs);
    info.lastBindTime = std::chrono::time_point_cast<std::chrono::milliseconds>(lastBindTimeMs);
    info.uploadedTime = std::chrono::time_point_cast<std::chrono::milliseconds>(uploadedTimeMs);

    return in;
}

template<>
egt::oUniStream& operator<< (egt::oUniStream& out, const ::GlProfilerInternals::GLProfilerContext& context)
{
    out << context.lastBinded
        << context.textures
        << context.generatedCount
        << context.uploadedCount
        << context.videoMemoryUsage
        << context.unloadedMemory
        << context.unloadedTextures;

    return out;
}

///////////////////////////////////////////////////////////////////////////
template<>
egt::iUniStream& operator>> (egt::iUniStream& in, ::GlProfilerInternals::GLProfilerContext& context)
{
    in  >> context.lastBinded
        >> context.textures
        >> context.generatedCount
        >> context.uploadedCount
        >> context.videoMemoryUsage
        >> context.unloadedMemory
        >> context.unloadedTextures;

    return in;
}

void stat_GenerateTexture(GLsizei n, GLuint *textures, std::vector<TextureMonitoring>& monitoringInfo, ::GlProfilerInternals::GLProfilerContext& context)
{
    for (size_t i = 0; i < (size_t)n; i++)
    {
        auto id = textures[i];
        if (context.textures.find(id) != context.textures.end())
        {
            // hmmm ...
            throw "hmmm ..";
        }
        monitoringInfo[i].status = TextureMonitoring::TexStatus::TexGenerated;
        monitoringInfo[i].generatedTime = std::chrono::steady_clock::now();
        monitoringInfo[i].lastBindTime = monitoringInfo[i].generatedTime;

        context.textures[id] = monitoringInfo[i];
    }
    context.generatedCount += n;
    context.lastBinded = textures[n - 1];
}

void GenerateTexture(GLsizei n, GLuint *textures, std::vector<TextureMonitoring> monitoringInfo)
{
    glGenTextures(n, textures);

#if defined(EGT_GPU_PROFILING_ON)
    if (monitoringInfo.size() != (size_t)n)
    {
        throw ("NA BABA TI FURKATA");
    }
    //
    {
        std::lock_guard<std::mutex> lock(::GlProfilerInternals::s_mainProfiler.locker);
        stat_GenerateTexture(n, textures, monitoringInfo, ::GlProfilerInternals::s_mainProfiler);
    }
#endif
}

void stat_BindTexture(GLenum target, GLuint texture, ::GlProfilerInternals::GLProfilerContext& context)
{
    if (texture == 0)
    {
        context.lastBinded = 0;
        return;
    }
    auto it = context.textures.find(texture);
    if (it == context.textures.end())
    {
        throw("cant bind");
    }
    auto& info = it->second;
    info.lastBindTime = std::chrono::steady_clock::now();
    if(info.status == TextureMonitoring::TexStatus::TexLoaded)
    {
        info.bindCount++;
    }
    context.lastBinded = texture;
}


void BindTexture(GLenum target, GLuint texture)
{
    glBindTexture(target, texture);
#if defined(EGT_GPU_PROFILING_ON)
    //
    {
        std::lock_guard<std::mutex> lock(::GlProfilerInternals::s_mainProfiler.locker);
        stat_BindTexture(target, texture, ::GlProfilerInternals::s_mainProfiler);
    }
#endif
}

void stat_TexImage2D(GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels,
                     ::GlProfilerInternals::GLProfilerContext& context)
{
    if (context.lastBinded == 0)
    {
        throw("Null texture id");
    }
    auto it = context.textures.find(context.lastBinded);
    if (it == context.textures.end())
    {
        throw("Texture not found");
    }
    auto& info = it->second;

    if (info.status == TextureMonitoring::TexStatus::TexLoaded)
    {
        context.uploadedCount--;
        context.videoMemoryUsage -= (width * height * info.pixelSize);
    }

    info.hasWidth = info.hasHeight = info.hasPixelSize = true;
    info.width = width;
    info.height = height;

    if (format == GL_RGB)
    {
        info.pixelSize = 3;
    }
    else if (format == GL_RGBA)
    {
        info.pixelSize = 4;
    }
    else
    {
        info.pixelSize = 1;
    }
    info.status = TextureMonitoring::TexStatus::TexLoaded;

    context.uploadedCount++;
    context.videoMemoryUsage += (width * height * info.pixelSize);

    info.uploadedTime = std::chrono::steady_clock::now();
}


void TexImage2D(GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels)
{
    glTexImage2D(target, level, internalFormat, width, height, border, format, type, pixels);
    //
#if defined(EGT_GPU_PROFILING_ON)
    {
        std::lock_guard<std::mutex> lock(::GlProfilerInternals::s_mainProfiler.locker);
        stat_TexImage2D(target, level, internalFormat, width, height, border, format, type, pixels, ::GlProfilerInternals::s_mainProfiler);
    }
#endif
}

void stat_DeleteTextures(GLsizei n, const GLuint *textures, ::GlProfilerInternals::GLProfilerContext& context, bool shouldThrow = true)
{
    for (int i = 0; i < n; i++)
    {
        if (textures[i] == 0)
        {
            continue;
        }
        auto it = context.textures.find(textures[i]);
        if (it == context.textures.end())
        {
            // hmm
            if (shouldThrow)
            {
                throw "Unknown texture";
            }
            else
            {
                continue;
            }
        }
        auto& info = it->second;
        if (info.hasWidth == false || info.hasHeight == false || info.hasPixelSize == false)
        {
            if (shouldThrow)
            {
                throw "Unknwon size";
            }
            else
            {
                continue;
            }
        }

        if (info.status != TextureMonitoring::TexStatus::TexLoaded)
        {
            if (shouldThrow)
            {
                throw "Not loaded texture";
            }
            else
            {
                continue;
            }
        }

        auto memSize = (info.width * info.height * info.pixelSize);


        context.unloadedMemory += memSize;
        context.videoMemoryUsage -= memSize;
        context.textures.erase(it);
    }

    context.uploadedCount -= n;
    context.generatedCount -= n;
    context.unloadedTextures += n;
}

void DeleteTextures(GLsizei n, const GLuint *textures)
{
    glDeleteTextures(n, textures);
#if defined(EGT_GPU_PROFILING_ON)
    //
    {
        std::lock_guard<std::mutex> lock(::GlProfilerInternals::s_mainProfiler.locker);
        stat_DeleteTextures(n, textures, ::GlProfilerInternals::s_mainProfiler);
    }
#endif
}

void StartCustomGlProfiling(int id)
{
#if defined(EGT_GPU_PROFILING_ON)
    std::lock_guard<std::mutex> customLocker(::GlProfilerInternals::s_mainCustomLocker);
    std::lock_guard<std::mutex> mainLock(::GlProfilerInternals::s_mainProfiler.locker);
    ::GlProfilerInternals::s_customProfiles[id] = ::GlProfilerInternals::s_mainProfiler;
    ::GlProfilerInternals::s_isCustomProfilingOn.store(true);
#endif
}

void StopCustomGlProfiling(int id, egt::NetMsg& msg)
{
#if defined(EGT_GPU_PROFILING_ON)
    std::lock_guard<std::mutex> customLocker(::GlProfilerInternals::s_mainCustomLocker);
    std::lock_guard<std::mutex> mainLock(::GlProfilerInternals::s_mainProfiler.locker);
    //
    UniMsg myMsg;
    myMsg.AddValue("custom_profiling_start", ::GlProfilerInternals::s_customProfiles[id]);
    myMsg.AddValue("custom_profiling_end", ::GlProfilerInternals::s_mainProfiler);
    msg.payload = myMsg.Serialize();
    ::GlProfilerInternals::s_customProfiles.erase(id);
    ::GlProfilerInternals::s_isCustomProfilingOn.store(false);
#endif
}

//
void DumpGlInfo( egt::NetMsg& netMsg )
{
#if defined(EGT_GPU_PROFILING_ON)
    UniMsg myMsg;

    {
        std::lock_guard<std::mutex> locker(::GlProfilerInternals::s_mainProfiler.locker);
        myMsg.AddValue("main", ::GlProfilerInternals::s_mainProfiler);
        myMsg.AddValue("custom_profiling", ::GlProfilerInternals::s_isCustomProfilingOn.load());
    }

    netMsg.payload = myMsg.Serialize();
#endif
}
}
