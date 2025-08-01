// ======= CrowdMomentum.h =======
#ifndef CROWD_MOMENTUM_H
#define CROWD_MOMENTUM_H

#include <string>
#include <vector>

class MomentumMeter;
class Team;
class Player;
class Crowd;
class PlayEvent;
class HypeAction;
class UIController;

// ------------------- GameMatch -------------------
class GameMatch {
private:
    int currentScore;
    float timeRemaining;
    int currentQuarter;
    MomentumMeter* momentumMeter;
    Team* homeTeam;
    Team* awayTeam;

public:
    GameMatch(Team* home, Team* away);
    void updateScore(int points);
    void updateTime(float deltaTime);
    void triggerPlayEvent(PlayEvent& event);
};

// ------------------- MomentumMeter -------------------
class MomentumMeter {
private:
    int momentumValue;
    float homeAdvantageFactor;

public:
    MomentumMeter();
    void increaseMomentum(int points);
    void decreaseMomentum(int points);
    std::string getMomentumStatus() const;
};

// ------------------- Crowd -------------------
class Crowd {
private:
    int energyLevel;
    std::string teamAffiliation;
    float soundIntensity;

public:
    Crowd(const std::string& affiliation);
    void cheer();
    void boo();
    void adjustEnergyBasedOnPlay(const PlayEvent& event);
};

// ------------------- Player -------------------
class Player {
private:
    std::string name;
    std::string position;
    int morale;
    float stamina;

public:
    Player(const std::string& playerName, const std::string& playerPosition);
    void performPlay(const std::string& playType);
    void reactToMomentumChange(const std::string& momentumStatus);
};

// ------------------- Team -------------------
class Team {
private:
    std::string teamName;
    std::vector<Player> players;
    std::string coach;

public:
    Team(const std::string& name, const std::string& coachName);
    void addPlayer(const Player& player);
    void updateTeamMorale(const std::string& momentumStatus);
    void executeStrategy();
};

// ------------------- PlayEvent -------------------
class PlayEvent {
private:
    std::string playType;
    bool success;
    int pointsEarned;
    bool penaltyFlag;

public:
    PlayEvent(const std::string& type);
    void resolveEvent();
    int calculateMomentumImpact() const;
};

// ------------------- HypeAction -------------------
class HypeAction {
private:
    std::string actionType;
    float timingWindow;
    float successRate;

public:
    HypeAction(const std::string& type, float window, float rate);
    void executeAction();
    void applyMomentumBonus();
};

// ------------------- UIController -------------------
class UIController {
private:
    std::string momentumBarDisplay;
    std::string hypeActionPrompt;

public:
    void updateUI(int momentumValue);
    void showQuickTimeEvent(const std::string& actionType);
};

#endif // CROWD_MOMENTUM_H


// ======= CrowdMomentum.cpp =======
#include "CrowdMomentum.h"
#include <iostream>
using namespace std;

// ------------------- GameMatch -------------------
GameMatch::GameMatch(Team* home, Team* away)
    : currentScore(0), timeRemaining(60.0f), currentQuarter(1),
      momentumMeter(new MomentumMeter()), homeTeam(home), awayTeam(away) {}

void GameMatch::updateScore(int points) {
    currentScore += points;
}

void GameMatch::updateTime(float deltaTime) {
    timeRemaining -= deltaTime;
    if (timeRemaining <= 0) {
        currentQuarter++;
        timeRemaining = 15.0f; // reset for next quarter
    }
}

void GameMatch::triggerPlayEvent(PlayEvent& event) {
    event.resolveEvent();
    int momentumImpact = event.calculateMomentumImpact();
    momentumMeter->increaseMomentum(momentumImpact);
}

// ------------------- MomentumMeter -------------------
MomentumMeter::MomentumMeter()
    : momentumValue(0), homeAdvantageFactor(1.0f) {}

void MomentumMeter::increaseMomentum(int points) {
    momentumValue += points;
    if (momentumValue > 100) momentumValue = 100;
}

void MomentumMeter::decreaseMomentum(int points) {
    momentumValue -= points;
    if (momentumValue < -100) momentumValue = -100;
}

string MomentumMeter::getMomentumStatus() const {
    if (momentumValue > 50) return "High Momentum";
    if (momentumValue < -50) return "Low Momentum";
    return "Neutral Momentum";
}

// ------------------- Crowd -------------------
Crowd::Crowd(const string& affiliation)
    : energyLevel(50), teamAffiliation(affiliation), soundIntensity(0.0f) {}

void Crowd::cheer() {
    cout << "Crowd cheers loudly!" << endl;
    energyLevel += 5;
}

void Crowd::boo() {
    cout << "Crowd boos in disappointment!" << endl;
    energyLevel -= 5;
}

void Crowd::adjustEnergyBasedOnPlay(const PlayEvent& event) {
    energyLevel += event.calculateMomentumImpact();
}

// ------------------- Player -------------------
Player::Player(const string& playerName, const string& playerPosition)
    : name(playerName), position(playerPosition), morale(100), stamina(100.0f) {}

void Player::performPlay(const string& playType) {
    cout << name << " performs play: " << playType << endl;
    stamina -= 5;
}

void Player::reactToMomentumChange(const string& momentumStatus) {
    cout << name << " reacts to " << momentumStatus << endl;
}

// ------------------- Team -------------------
Team::Team(const string& name, const string& coachName)
    : teamName(name), coach(coachName) {}

void Team::addPlayer(const Player& player) {
    players.push_back(player);
}

void Team::updateTeamMorale(const string& momentumStatus) {
    cout << "Team morale adjusts based on: " << momentumStatus << endl;
}

void Team::executeStrategy() {
    cout << "Team executes strategy!" << endl;
}

// ------------------- PlayEvent -------------------
PlayEvent::PlayEvent(const string& type)
    : playType(type), success(false), pointsEarned(0), penaltyFlag(false) {}

void PlayEvent::resolveEvent() {
    success = true;
    pointsEarned = 7;
}

int PlayEvent::calculateMomentumImpact() const {
    return success ? pointsEarned : -5;
}

// ------------------- HypeAction -------------------
HypeAction::HypeAction(const string& type, float window, float rate)
    : actionType(type), timingWindow(window), successRate(rate) {}

void HypeAction::executeAction() {
    cout << "Executing hype action: " << actionType << endl;
}

void HypeAction::applyMomentumBonus() {
    cout << "Momentum boosted by hype action!" << endl;
}

// ------------------- UIController -------------------
void UIController::updateUI(int momentumValue) {
    cout << "Updating UI with momentum: " << momentumValue << endl;
}

void UIController::showQuickTimeEvent(const string& actionType) {
    cout << "Quick time event for action: " << actionType << endl;
}


// ======= main.cpp =======
#include "CrowdMomentum.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

PlayEvent randomPlayEvent(const string& description) {
    PlayEvent event(description);
    bool success = rand() % 2;
    if (success) {
        event.resolveEvent();
    } else {
        cout << description << " failed!" << endl;
    }
    return event;
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    Team homeTeam("Tigers", "Coach Smith");
    Team awayTeam("Eagles", "Coach Brown");

    homeTeam.addPlayer(Player("John", "Quarterback"));
    homeTeam.addPlayer(Player("Alex", "Wide Receiver"));

    awayTeam.addPlayer(Player("Ryan", "Quarterback"));
    awayTeam.addPlayer(Player("Mark", "Running Back"));

    GameMatch match(&homeTeam, &awayTeam);

    MomentumMeter momentum;
    UIController ui;
    Crowd homeCrowd("Tigers");

    for (int i = 1; i <= 4; i++) {
        cout << "\n--- Play " << i << " ---" << endl;

        bool isHomeTeam = rand() % 2;
        if (isHomeTeam) {
            cout << "[Home Team Play]" << endl;
            PlayEvent event = randomPlayEvent("Touchdown Attempt");

            int impact = event.calculateMomentumImpact();
            momentum.increaseMomentum(impact);
            cout << "Momentum Status: " << momentum.getMomentumStatus() << endl;

            if (impact > 0) homeCrowd.cheer();
            else homeCrowd.boo();

            ui.updateUI(momentum.getMomentumStatus() == "High Momentum" ? 80 : 50);
            ui.showQuickTimeEvent(impact > 0 ? "Celebration" : "Frustration Gesture");
        } else {
            cout << "[Away Team Play]" << endl;
            PlayEvent event = randomPlayEvent("Touchdown Attempt");

            int impact = event.calculateMomentumImpact();
            momentum.decreaseMomentum(impact);
            cout << "Momentum Status: " << momentum.getMomentumStatus() << endl;

            if (impact > 0) homeCrowd.boo();
            else homeCrowd.cheer();

            ui.updateUI(momentum.getMomentumStatus() == "Low Momentum" ? 20 : 50);
            ui.showQuickTimeEvent(impact > 0 ? "Frustration Gesture" : "Celebration");
        }
    }

    return 0;
}

