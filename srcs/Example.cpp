#include <iostream>
#include <vector>

// hpp
class Room {
    public:
        virtual void connect(Room *room) = 0;

        virtual ~Room() {
        }
};

// hpp
class MagicRoom : public Room {
    public:
        MagicRoom() {
            // CPP
            std::cout << "creating MagicRoom" << std::endl;
        }

        void connect(Room *room) override {}
};

class MazeGame {
    private:
        std::vector<Room *> rooms;

    public:
        virtual Room* makeRoom() = 0;

        ~MazeGame() {
            std::cout << "desctuctor MazeGame" << std::endl;
            for (Room* ptr : rooms) {
                std::cout << "deleting room" << std::endl;
                delete ptr;
            }
        }
        // TODO implement destuctor

        void anOperation() {
            std::cout << "anOperation" << std::endl;
            Room* room1 = makeRoom();
            Room* room2 = makeRoom();
            room1->connect(room2);
            rooms.push_back(room1);
            rooms.push_back(room2);
        }
};

class MagicMazeGame : public MazeGame {
public:
    MagicMazeGame() {
        std::cout << "Constructor MagicMazeGame" << std::endl;
        anOperation();
    }

    Room* makeRoom() override {
        return new MagicRoom(); // factory
    }
};

int main() {
    MagicMazeGame maze = MagicMazeGame();
}
