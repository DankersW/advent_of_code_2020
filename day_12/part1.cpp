#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

int get_direction_index_left(int jump, int index)
{
    if (index - jump >= 0) { return index - jump; }
    else { return index - jump + 4; }
}

int get_direction_index_right(int jump, int index)
{
    if (jump + index < 4) { return jump + index; }
    else { return jump + index - 4; }
}

char calc_direction(const char &starting_direction, const char &heading, int turning_degrees)
{
    char directions[4] = {'N', 'E', 'S', 'W'};

    int jumps = turning_degrees / 90;
    int index_start_direction = std::distance(directions, std::find(directions, directions + 4, starting_direction));

    int direction_index = (heading == 'L') ? get_direction_index_left(jumps, index_start_direction) : 
                                             get_direction_index_right(jumps, index_start_direction);
    return directions[direction_index];
}

int main()
{
    int east_counter = 0;
    int north_counter = 0;
    char direction = 'E';

    std::ifstream file("input_test.txt");
    std::string line;
    while (std::getline(file, line))
    {
        char action = line[0];
        int value = std::stoi(line.substr(1));

        if (action == 'N' || (action == 'F' && direction == 'N')) { north_counter += value; }
        else if (action == 'S' || (action == 'F' && direction == 'S')) { north_counter -= value; }
        else if (action == 'E' || (action == 'F' && direction == 'E')) { east_counter += value; }
        else if (action == 'W' || (action == 'F' && direction == 'W')) { east_counter -= value; }
        else if (action == 'L' || action == 'R') { direction = calc_direction(direction, action, value); }
    }

    int distance =  abs(north_counter) + abs(east_counter);
    std::cout << "manhatten distance: " << distance << std::endl;

    return 0;
}