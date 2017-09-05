/*
 * Velislav Velkov
 */

#include "ImagesWidget.h"

ImagesWidget::ImagesWidget ( int maxGuesses, Wt::WContainerWidget *parent ) : Wt::WContainerWidget ( parent )
{
    for ( int i = 0; i < maxGuesses; ++i )
    {
        std::string fname = "data/hangman";
        fname += boost::lexical_cast<std::string> ( i ) + ".jpg";
        Wt::WImage *theImage = new Wt::WImage ( fname, this );
        images_.push_back ( theImage );

        theImage->hide();
    }

    Wt::WImage *hurray = new Wt::WImage ( "data/hangmanhurray.jpg", this );
    hurray->show();
    images_.push_back ( hurray );

    showImage ( false );
}

void ImagesWidget::showImage ( bool bShow )
{
    for( unsigned int i = 0; i < images_.size()-1; i++ )
        bShow ? images_[i]->show() : images_[i]->hide();
//     image ( index )->hide();
//     image_ = index;
//     image ( index )->show();
}

Wt::WImage *ImagesWidget::image ( int index ) const
{
    return index == int(EStatus::HURRAY) ? images_.back() : images_[index];
}
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
