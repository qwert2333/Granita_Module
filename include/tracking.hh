#ifndef TRACKING_HH
#define TRACKING_HH

#include "G4UserTrackingAction.hh"
#include "action.hh"

#include "G4UserEventAction.hh"


class MyEventAction;

class MyTrackingAction : public G4UserTrackingAction {
public:
    MyTrackingAction(MyEventAction* eventAction);
    virtual ~MyTrackingAction(); // Ensure this declaration exists
    virtual void PreUserTrackingAction(const G4Track* track) override;

private:
    MyEventAction* fEventAction;
};

#endif

