
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Valve {
    public:
        string name;
        int flow_rate;
        vector<string> output_valves;
        static Valve* from_line(string line) {
            Valve* valve = new Valve();
            stringstream stream(line);
            stream >> valve->name;
            stream >> valve->flow_rate;
            string output_valve;
            while (stream >> output_valve) {
                valve->output_valves.push_back(output_valve);
            }
            return valve;
        }
        void print() {
            cout << this->name << ": flow_rate=" << this->flow_rate << " (";
            bool commas = false;
            for (vector<string>::iterator it =
                    this->output_valves.begin();
                    it != this->output_valves.end();
                    ++it) {
                if (commas) {
                    cout << ", ";
                }
                cout << *it;
                commas = true;
            }
            cout << ")";
        }
};

class Network {
    public:
        int valves_with_flow_rate;
        unordered_map<string, Valve*> valves;
        Network() {
            this->valves_with_flow_rate = 0;
        }
        void read_input() {
            string line;
            while (getline(cin, line)) {
                Valve* valve = Valve::from_line(line);
                valves.insert(make_pair(valve->name, valve));
                if (valve->flow_rate > 0) {
                    valves_with_flow_rate++;
                }
            }
        }
        void print() {
            cout << "Network:" << endl;
            for (unordered_map<string, Valve*>::iterator it =
                    this->valves.begin();
                    it != this->valves.end();
                    ++it) {
                it->second->print();
                cout << endl;
            }
        }
};

class State {
    public:
        Network* network;
        int minute, pressure_released;
        Valve* current_valve;
        unordered_set<string> valves_open;
        unordered_set<string> valves_seen_since_last_open;
        State(Network* network, string current_valve_name, int minute,
              int pressure_released) {
            this->network = network;
            this->move_to(current_valve_name);
            this->minute = minute;
            this->pressure_released = pressure_released;
        }
        void init() {
            this->move_to("AA");
            this->minute = 1;
        }
        void wait() {
            // cout << "wait()" << endl;
            this->step();
        }
        void move_to(string name) {
            // cout << "move_to(" << name << ")" << endl;
            this->current_valve = this->network->valves.at(name);
            this->valves_seen_since_last_open.insert(name);
            this->step();
        }
        void open_valve() {
            // cout << "open_valve( " << this->current_valve->name << ")" << endl;
            this->step();
            this->valves_open.insert(this->current_valve->name);
            this->valves_seen_since_last_open.clear();
        }
        void print() {
            cout << "current_valve=" << this->current_valve->name << " minute=" << this->minute << " pressure_released=" << this->pressure_released << endl;
        }
        bool valves_left_to_open() {
            return this->network->valves_with_flow_rate >
                this->valves_open.size();
        }
        bool is_time_left() {
            return this->minute <= 30;
        }
        void step() {
            for (unordered_set<string>::iterator it =
                    this->valves_open.begin();
                    it != this->valves_open.end();
                    ++it) {
                Valve* valve = this->network->valves.at(*it);
                pressure_released += valve->flow_rate;
            }
            minute++;
        }
        State* clone() {
            State* state = new State(this->network,
                                     this->current_valve->name,
                                     this->minute,
                                     this->pressure_released);
            for (unordered_set<string>::iterator it =
                    this->valves_open.begin();
                    it != this->valves_open.end();
                    ++it) {
                state->valves_open.insert(*it);
            }
            for (unordered_set<string>::iterator it =
                    this->valves_seen_since_last_open.begin();
                    it != this->valves_seen_since_last_open.end();
                    ++it) {
                state->valves_seen_since_last_open.insert(*it);
            }
            return state;
        }
};

int solution(Network* network) {
    State* state = new State(network, "AA", 1, 0);
    queue<State*> states;
    states.push(state);
    vector<State*> finished_states;
    State* new_state;
    while (states.size() > 0) {
        state = states.front();
        // state->print();
        if (! state->is_time_left()) {
            states.pop();
            finished_states.push_back(state);
            continue;
        }
        if (! state->valves_left_to_open()) {
            state->wait();
            continue;
        }
        states.pop();
        // If we haven't opened this valve and it has pressure,
        // crack it open!
        if (state->valves_open.find(state->current_valve->name) ==
                state->valves_open.end() &&
                state->current_valve->flow_rate > 0) {
            new_state = state->clone();
            new_state->open_valve();
            states.push(new_state);
        }
        for (vector<string>::iterator it =
                state->current_valve->output_valves.begin();
                it != state->current_valve->output_valves.end();
                ++it) {
            // Skip if we've already seen this valve since the last
            // valve opening
            if (state->valves_seen_since_last_open.find(*it) !=
                    state->valves_seen_since_last_open.end()) {
                continue;
            }
            new_state = state->clone();
            new_state->move_to(*it);
            states.push(new_state);
        }
    }
    int max_released = 0;
    for (vector<State*>::iterator it = finished_states.begin();
            it != finished_states.end();
            ++it) {
        if ((*it)->pressure_released > max_released) {
            max_released = (*it)->pressure_released;
        }
    }
    return max_released;
}

int main() {
    Network* network = new Network();
    network->read_input();
    // network->print();
    cout << solution(network) << endl;
    return 0;
}
