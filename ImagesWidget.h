/*
 * Velislav Velkov
 */

#ifndef IMAGESWIDGET_H
#define IMAGESWIDGET_H

#include <Wt/WContainerWidget>
#include <Wt/WImage>

#include <vector>

class ImagesWidget : public Wt::WContainerWidget
{
public:
    enum class EStatus : int
    {
        none, HURRAY
    };
    ImagesWidget ( int maxGuesses, Wt::WContainerWidget *parent );
    std::vector<Wt::WImage *> images_;
    void showImage ( bool bShow );
    Wt::WImage *image ( int index ) const;
    int image_;
};

#endif // IMAGESWIDGET_H
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
