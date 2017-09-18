#ifndef __EGT_GL_OLD_PROFILER_H__
#define __EGT_GL_OLD_PROFILER_H__


#include <cstdint>
#include <vector>
#include <chrono>
#include <string>
#include <mutex>
#include <map>

//#define EGT_GPU_PROFILING_ON

namespace egt {

struct TextureMonitoring
{
    bool operator<(const TextureMonitoring& t2) const
    {
        if(allocatorName != t2.allocatorName)
        {
            return allocatorName < t2.allocatorName;
        }
        if(imageName != t2.imageName)
        {
            return imageName < t2.imageName;
        }

        return false;
    }



    enum class TexStatus
    {
        TexNotLoaded,
        TexGenerated,
        TexLoaded,
    };

    bool hasGameId = false;
    bool hasImageName = false;
    bool hasAllocatorName = false;
    bool hasWidth = false;
    bool hasHeight = false;
    bool hasPixelSize = false;
    //
    int gameId = 0;
    std::string imageName;
    std::string allocatorName;
    int width = 0;
    int height = 0;
    int pixelSize = 0;
    int textureId = 0;
    int bindCount = 0;
    //
    std::chrono::steady_clock::time_point generatedTime;
    std::chrono::steady_clock::time_point lastBindTime;
    std::chrono::steady_clock::time_point uploadedTime;
    //
    TexStatus status = TexStatus::TexNotLoaded;
};

void GenerateTexture( int32_t n, uint32_t *textures, std::vector<TextureMonitoring> monitoringInfo);
void BindTexture( unsigned int target, uint32_t texture );
void TexImage2D( unsigned int target, int32_t level,
                    int32_t internalFormat,
                    int32_t width, int32_t height,
                    int32_t border, unsigned int format, unsigned int type,
                    const void *pixels );

void DeleteTextures( int32_t n, const uint32_t *textures);
//

class NetMsg;
void StartCustomGlProfiling(int id);
void StopCustomGlProfiling(int id, egt::NetMsg& msg);
void DumpGlInfo( egt::NetMsg& netMsg );
}

namespace GlProfilerInternals
{

struct GLProfilerContext
{
    GLProfilerContext() = default;
    GLProfilerContext(GLProfilerContext&& rhs)
    {
        lastBinded = rhs.lastBinded;
        textures = std::move(rhs.textures);
        generatedCount = rhs.generatedCount;
        uploadedCount = rhs.uploadedCount;
        videoMemoryUsage = rhs.videoMemoryUsage;
        unloadedMemory = rhs.unloadedMemory;
        unloadedTextures = rhs.unloadedTextures;
    }

    GLProfilerContext& operator=(GLProfilerContext&& rhs)
    {
        lastBinded = rhs.lastBinded;
        textures = std::move(rhs.textures);
        generatedCount = rhs.generatedCount;
        uploadedCount = rhs.uploadedCount;
        videoMemoryUsage = rhs.videoMemoryUsage;
        unloadedMemory = rhs.unloadedMemory;
        unloadedTextures = rhs.unloadedTextures;

        return *this;
    }

    GLProfilerContext(const GLProfilerContext& rhs)
    {
        lastBinded = rhs.lastBinded;
        textures = (rhs.textures);
        generatedCount = rhs.generatedCount;
        uploadedCount = rhs.uploadedCount;
        videoMemoryUsage = rhs.videoMemoryUsage;
        unloadedMemory = rhs.unloadedMemory;
        unloadedTextures = rhs.unloadedTextures;
    }

    GLProfilerContext& operator=(const GLProfilerContext& rhs)
    {
        lastBinded = rhs.lastBinded;
        textures = (rhs.textures);
        generatedCount = rhs.generatedCount;
        uploadedCount = rhs.uploadedCount;
        videoMemoryUsage = rhs.videoMemoryUsage;
        unloadedMemory = rhs.unloadedMemory;
        unloadedTextures = rhs.unloadedTextures;

        return *this;
    }

    std::mutex locker = {};
    uint32_t lastBinded = 0;

    std::map<uint32_t, ::egt::TextureMonitoring> textures;

    int generatedCount = 0;
    int uploadedCount = 0;
    int64_t videoMemoryUsage = 0;

    int64_t unloadedMemory = 0;
    int64_t unloadedTextures = 0;
};
}


#endif // __EGT_GL_OLD_PROFILER_H__
