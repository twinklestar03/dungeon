#include "game/Room.hpp"


Room::Room(std::string room_name, uint32_t max_x, uint32_t max_y) {
    this->room_name = room_name;
    this->max_x = max_x;
    this->max_y = max_y;

    this->map = std::vector<std::vector<MapObject>>(
        max_x, std::vector<MapObject>(max_y, MapObject::WALL));
}

Room::~Room() {
    // delete entities.
    // delete items.
}

bool Room::isWall(const Location& loc) {
    if (loc.getX() >= this->max_x || loc.getY() >= this->max_y) {
        return true;
    }

    return this->map[loc.getX()][loc.getY()] == MapObject::WALL;
}

bool Room::isOutside(const Location& loc) {
    if (this->room_name != loc.getRoomId()) {
        return false;
    }

    if (loc.getX() >= this->max_x || loc.getY() >= this->max_y) {
        return true;
    }

    if (loc.getX() < 0 || loc.getY() < 0) {
        return true;
    }

    return false;
}

void Room::generate() {
    srand(time(NULL));
    
    std::random_device rd;
    std::default_random_engine generator( rd() );
    std::uniform_int_distribution<uint32_t> uni_x(0, this->max_x - 1);
    std::uniform_int_distribution<uint32_t> uni_y(0, this->max_y - 1);

    // Fill with walls.
    for (uint32_t x = 0; x < this->max_x; x++) {
        for (uint32_t y = 0; y < this->max_y; y++) {
            this->map[x][y] = MapObject::WALL;
        }
    }

    // Glow-tree algorithm for maze generation.
    Location start_point = {uni_x(rd), uni_y(rd)};
    std::cerr << "Starting Point: " << start_point.getX() << ", " << start_point.getY() << std::endl;

    std::vector<std::vector<bool>> visited(this->max_x, std::vector<bool>(this->max_y, false));
    std::vector<Location> stack;
    stack.push_back(start_point);

    while ( !stack.empty() ) {
        Location &current = stack.back();

        visited[current.getX()][current.getY()] = true;

        // Replace wall with floor.
        this->map[current.getX()][current.getY()] = MapObject::FLOOR;

        // Randomly choose unvisited neighbors.
        std::vector<Location> neighbors;
        if (current.getX() > 1 && !visited[current.getX() - 1][current.getY()]) {
            neighbors.push_back({current.getX() - 1, current.getY()});
            
        }
        if (current.getX() < this->max_x - 2 && !visited[current.getX() + 1][current.getY()]) {
            neighbors.push_back({current.getX() + 1, current.getY()});

        }
        if (current.getY() > 1 && !visited[current.getX()][current.getY() - 1]) {
            neighbors.push_back({current.getX(), current.getY() - 1});
        }
        if (current.getY() < this->max_y - 2 && !visited[current.getX()][current.getY() + 1]) {
            neighbors.push_back({current.getX(), current.getY() + 1});
        }

        std::uniform_int_distribution<uint32_t> uni_neighbor(0, neighbors.size() - 1);
        Location &next = neighbors[uni_neighbor(rd) % neighbors.size()];
        // Push next location into stack.
        stack.push_back(next);

    }
}


void Room::dumpMapInfo() {
    // Dump map info.
    std::cerr << "Dumping Map Informations...\n";
    for (uint32_t y = 0; y < this->max_y; y++) {
        for (uint32_t x = 0; x < this->max_x; x++) {
            if (this->map[x][y] == MapObject::WALL) {
                std::cout << "W";
            } else if (this->map[x][y] == MapObject::FLOOR) {
                std::cout << "F";
            } else {
                std::cout << "N";
            }
        }
        std::cout << std::endl;
    }
}