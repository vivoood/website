/*
 * Velislav Velkov
 */

#ifndef HANGMANWIDGET_H
#define HANGMANWIDGET_H

#include <string>

#include <Wt/WContainerWidget>
#include <Wt/WComboBox>
#include <Wt/WPushButton>

#include "ImagesWidget.h"

class HangmanWidget : public Wt::WContainerWidget
{
public:
    HangmanWidget ( const std::string &name, Wt::WContainerWidget *parent = 0 );
    Wt::Signal<int>& scoreUpdated();
    void newGame();
    void registerGuess ( char c );
private:
    Wt::WText        *title_;
//     WordWidget       *word_;
    ImagesWidget     *images_;
//     LettersWidget    *letters_;
    Wt::WText        *statusText_;
    Wt::WComboBox    *language_;
    Wt::WPushButton  *newGameButton_;
//
    Wt::Signal<int>   scoreUpdated_;

    std::string       name_;
//     Dictionary        dictionary_;
    int               badGuesses_;
//
//     void registerGuess ( char c );
//     void newGame();
};

#endif // HANGMANWIDGET_H
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
