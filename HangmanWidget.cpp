/*
 * Velislav Velkov
 */

#include "HangmanWidget.h"

#include <Wt/WText>
#include <Wt/WBreak>

#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WTemplate>
#include <Wt/WHBoxLayout>

#define MaxGuesses 5

HangmanWidget::HangmanWidget ( const std::string& name, Wt::WContainerWidget* parent )
    : WContainerWidget ( parent ),
      name_ ( name ),
      badGuesses_ ( 0 )
{
    setContentAlignment ( Wt::AlignCenter );
    title_ = new Wt::WText ( tr ( "hangman.readyToPlay" ), this );
    title_->setStyleClass ( "youHang" );
    statusText_ = new Wt::WText ( this );
    images_ = new ImagesWidget ( MaxGuesses, this );

    language_ = new Wt::WComboBox ( this );
    language_->setStyleClass ( "ComboStyle" );
    language_->addItem ( "English" );
    language_->addItem ( "German" );
    language_->addItem ( "Bulgarian" );

    new Wt::WBreak ( this );

    newGameButton_ = new Wt::WPushButton ( "New Game", this );
    newGameButton_->setStyleClass ( "newGame" );
    newGameButton_->clicked().connect ( this, &HangmanWidget::newGame );

    Wt::WContainerWidget *container = new Wt::WContainerWidget ( this );
    container->setStyleClass ( "yellow-box" );

    Wt::WHBoxLayout *hbox = new Wt::WHBoxLayout ( container );
    container->setLayout ( hbox );

    Wt::WText *item = new Wt::WText ( "Item 1", container );
    item->setStyleClass ( "green-box" );
    hbox->addWidget ( item );

    item = new Wt::WText ( "Item 2", container );
    item->setStyleClass ( "blue-box" );
    hbox->addWidget ( item );

    Wt::WTemplate *t = new Wt::WTemplate ( Wt::WString::tr ( "WTemplate-example" ) );
    t->bindWidget ( "name-edit", new Wt::WLineEdit (  ) );
    t->bindWidget ( "save-button", new Wt::WPushButton ( "Save" ) );
    t->bindWidget ( "cancel-button", new Wt::WPushButton ( "Cancel" ) );
    this->addWidget(t);
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
