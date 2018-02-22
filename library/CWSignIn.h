#ifndef CWSIGNIN_H
#define CWSIGNIN_H

#include <Wt/WContainerWidget>

class CWLineEditField;
class CWUser;

class CWSignIn : public Wt::WContainerWidget
{
private:
    friend class Factory;
    CWSignIn ( std::string usrhash, std::string strPayload, Wt::WContainerWidget* parent = 0 );
    void FillData(CWUser &);
    
    std::map<std::string, CWLineEditField*> vData = { {"e-mail", nullptr}, {"Password", nullptr}, {"Username", nullptr}, {"Country", nullptr}, {"Gender", nullptr} };
};

#endif //CWSIGNIN_H

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
