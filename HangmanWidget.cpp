/*
 * Velislav Velkov
 */

#include "HangmanWidget.h"

#include <Wt/WText>
#include <Wt/WBreak>

#define MaxGuesses 5

HangmanWidget::HangmanWidget ( const std::string& name, Wt::WContainerWidget* parent )
    : WContainerWidget ( parent ),
      name_ ( name ),
      badGuesses_ ( 0 )
{
    setContentAlignment ( Wt::AlignCenter );
    title_ = new Wt::WText ( tr ( "hangman.readyToPlay" ), this );
    statusText_ = new Wt::WText ( this );
    images_ = new ImagesWidget ( MaxGuesses, this );

    language_ = new Wt::WComboBox ( this );
    language_->addItem ( tr ( "hangman.englishWords" ).arg ( 18957 ) );
    language_->addItem ( tr ( "hangman.dutchWords" ).arg ( 1688 ) );

    new Wt::WBreak ( this );

    newGameButton_ = new Wt::WPushButton ( tr ( "hangman.newGame" ), this );
    newGameButton_->clicked().connect ( this, &HangmanWidget::newGame );
}

Wt::Signal<int> & HangmanWidget::scoreUpdated()
{
    return scoreUpdated_;
}

void HangmanWidget::newGame()
{
    Wt::WString title ( tr ( "hangman.guessTheWord" ) );
    title_->setText ( title.arg ( name_ ) );

    language_->hide();
    newGameButton_->hide();

//     Dictionary dictionary = ( Dictionary ) language_->currentIndex();
//     word_->init ( RandomWord ( dictionary ) );
//     letters_->reset();
    badGuesses_ = 0;
    images_->showImage ( true );
    statusText_->setText ( "" );
}

void HangmanWidget::registerGuess ( char c )
{
//     bool correct = word_->guess ( c );

//     if ( !correct )
    {
        ++badGuesses_;
        images_->showImage ( badGuesses_ );
    }

    if ( badGuesses_ == MaxGuesses )
    {
        Wt::WString status ( tr ( "hangman.youHang" ) );
        statusText_->setText ( status.arg ( "WWW" ) );

//         letters_->hide();
        language_->show();
        newGameButton_->show();

        scoreUpdated_.emit ( -10 );
    }
    else if ( badGuesses_ > MaxGuesses )
    {
        statusText_->setText ( tr ( "hangman.youWin" ) );
        images_->showImage ( int ( ImagesWidget::EStatus::HURRAY ) );

//         letters_->hide();
        language_->show();
        newGameButton_->show();

        scoreUpdated_.emit ( 20 - badGuesses_ );
    }
}
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
