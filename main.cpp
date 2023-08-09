/*  COMP.CS.100 Project 2: Game statistics
 *
 *
 * Description:
 * The program acts as a game statistics. The program is given an input
 * file with three data fields on each line. The data file's lines should be
 * in format game_name;player_name;score. If the file is not found or the
 * format is not correct, the program execution is terminated.
 * The program stores the data in to a datastructure. After that, user can
 * give different commands to make searhes and add or delete entries from
 * the data. The commands can be written both in lower- and uppercase.
 * If a parameter consists of more than one word, quotation marks
 * should be used.
 *
 * The game statistics program has the following commands:
 * ALL_GAMES - Prints all known game names
 * GAME <game name> - Prints all players playing the given game
 * ALL_PLAYERS - Prints all known player names
 * PLAYER <player name> - Prints all games the given player plays
 * ADD_GAME <game name> - Adds a new game
 * ADD_PLAYER <game name> <player name> <score> - Adds a new player with the
 * given score for the given game, or updates the player's score if the player
 * already playes the game
 * REMOVE_PLAYER <player name> - Removes the player from all games
 * QUIT - Terminates the program without printing anything.
 *
 * Writers of this program:
 *
 * Krista Poutanen
 *
 * &
 *
 * Mikko Kaukonen
 */


#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>


using namespace std;
using GAMES = map<string, map<string, int>>;

// string constants
const string FILE_NOT_READ_TEXT = "Error: File could not be read.",
             INPUT_FILE_PROMPT = "Give a name for input file: ",
             FILE_FORMAT_INVALID_TEXT = "Error: Invalid format in file.",
             ALL_GAMES_PRINTOUT_HEADER_TEXT
             = "All games in alphabetical order:",
             ALL_PLAYERS_PRINTOUT_HEADER_TEXT
             = "All players in alphabetical order:",
             INVALID_INPUT_TEXT = "Error: Invalid input.",
             GAME_NOT_FOUND_TEXT = "Error: Game could not be found.",
             PLAYER_NOT_FOUND_TEXT = "Error: Player could not be found.",
             GAME_ALREADY_EXIST_TEXT = "Error: Already exists.",
             GAME_WAS_ADDED_TEXT = "Game was added.",
             PLAYER_WAS_ADDED_TEXT = "Player was added.",
             PLAYER_WAS_REMOVED_TEXT = "Player was removed from all games.";


// This function was ready in the program code base of the exercise.
// So not done by ourselves!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//
// Casual split func, if delim char is between "'s, ignores it.
vector<string> split( const string& str, char delim = ';' )
{
    vector<string> result = {""};
    bool inside_quatation = false;
    for ( auto current_char : str )
    {
        if ( current_char == '"' )
        {
            inside_quatation = not inside_quatation;
        }
        else if ( current_char == delim and not inside_quatation )
        {
            result.push_back("");
        }
        else
        {
            result.back().push_back(current_char);
        }
    }
    if ( result.back() == "" )
    {
        result.pop_back();
    }
    return result;
}

// Function that checks the format of a line
bool line_is_ok(vector<string> const &line_parts)
{
    // chekcs that vector consists of 3 parts
    // and that gamename and playername are not empty
    return line_parts.size() == 3
            && !line_parts.at(0).empty()
            && !line_parts.at(1).empty();

}


// Function that reads the file into two nested map vectors
bool read_file_input(GAMES &scoreboard)
{
    // Retrieving filename
    string filename;
    cout << INPUT_FILE_PROMPT;
    getline(cin, filename);


    // Open the file and check
    ifstream file(filename);

    if(!file)
    {
        cout << FILE_NOT_READ_TEXT << endl;
        return false;
    }

    // goes through the file and checks the file format
    string line = "";
    vector<string> line_parts;
    while(getline(file, line))
    {
        line_parts = split(line);

        if(!line_is_ok(line_parts))
        {
            cout << FILE_FORMAT_INVALID_TEXT << endl;
            file.close();
            return false;
        }

        // 0 = game, 1 = player, 2= score
        string gamename =
                line_parts.at(0),
                player = line_parts.at(1),
                points_str = line_parts.at(2);


        // checks if game is in database
        // if not, adds game to the database
        if(scoreboard.find(gamename) == scoreboard.end())
        {
            scoreboard.insert({gamename, {}});
        }

        // adds players score to the database
        scoreboard.at(gamename).insert({player, stoi(points_str)});

    }

    return true;
}


// Prints all games in alphabetical order with the ALL_GAMES command
void print_all_games(GAMES const &scoreboard)
{
    cout << ALL_GAMES_PRINTOUT_HEADER_TEXT << endl;
    for(auto & entry : scoreboard)
    {
        cout << entry.first<< endl;
    }

}

// Prints the players and scores of the game included in the GAME command
void print_players_and_scores (GAMES &scoreboard, string game_input)
{
    // Checks if game exists in data structure
    if (scoreboard.find(game_input) == scoreboard.end())
    {
        cout << GAME_NOT_FOUND_TEXT << endl;
    }
    else
    {
        cout << "Game " << game_input <<
                  " has these scores and players, listed in ascending order:"
                  << endl;

        // Creates data sturcture to store players and scores
        vector<pair<string, int>> playerscoreVector;

        // Adds players and scores to a vector of pairs
        if ((scoreboard.find(game_input) != scoreboard.end()))
        {
            auto &scoremap = scoreboard[game_input];
            for (auto iter = scoremap.begin();
                      iter != scoremap.end(); ++iter)
             {
                      playerscoreVector.push_back
                      (make_pair(iter->first,
                                 iter->second));
                            }
                    }

        // Return, if no players and scores for the game are found
        else
        {
            return;
        }

          // Sorts the vector of pairs by score
          sort(playerscoreVector.begin(),
               playerscoreVector.end(),
               [](auto &left, auto &right) {
               return left.second < right.second;});


           // Prints the players and scores. If two players have
           // the same score, they are printed on the same line
           int j = 1;
           for (unsigned int i = 0; i< playerscoreVector.size() ; i++)
            {
            if (playerscoreVector[i].second ==
                playerscoreVector[j].second)
            {
                cout << playerscoreVector[i].second << " : "
                << playerscoreVector[i].first << ", "
                << playerscoreVector[j].first
                << endl;
                i = i +1;
                j = j +1;
                        }
             else
             {
                cout << playerscoreVector[i].second << " : "
                     << playerscoreVector[i].first << endl;
}
             j = j +1;
                    }
                    }
    }


// Prints players names in alphabetical order with the ALL_PLAYERS command
void print_all_players(GAMES const &scoreboard)
{
    cout << ALL_PLAYERS_PRINTOUT_HEADER_TEXT << endl;

    // Creates data sturcture to store players
    map<string, int> players;

    for(auto & outer_map_pair : scoreboard)
        {
        for(auto & inner_map_pair : outer_map_pair.second)
            {

            // Store players in map
            if(players.find(inner_map_pair.first) == players.end())
               players.insert({inner_map_pair.first, {}});
            }
        }

        for(auto & pair : players)
        cout << pair.first<< endl;
}

// Prints all games named player has played in alphabetical order
// with the PLAYER and players name command
void print_named_player_games(GAMES const &scoreboard, string player_name)
{

    // Creates data sturcture to store the games player has played
    map<string, int> games;
    for(auto & outer_map_pair : scoreboard)
        {

        // Checks if player exists in each games data structure
        // and if store games
        if(outer_map_pair.second.find(player_name)
           != outer_map_pair.second.end())
        {
            games.insert({outer_map_pair.first, {}});
         }

        }

            // Checks the games vector.
            // If it isn't empty prints player and the games played.
            // Else prints player not found text.
            if(!games.empty())
            {
                cout << "Player " << player_name <<
                        " playes the following games:"<< endl;

                for(auto & pair : games)
                cout << pair.first << endl;
            }

            else
            {
                cout << PLAYER_NOT_FOUND_TEXT << endl;
            }

}

// Checks if a given game already exists and if not
// adds it in the scoreboars map with the add_game command
void add_new_game(GAMES  &scoreboard, string game_name)
{
    map<string, int> players_and_scores;

    // Checks if the added game allready exist
    if(scoreboard.find(game_name) != scoreboard.end())
    {
        cout << GAME_ALREADY_EXIST_TEXT << endl;
    }

    else
    {
        // Adds the new game in the scoreboard map
        scoreboard.insert({game_name, players_and_scores});

        cout << GAME_WAS_ADDED_TEXT << endl;
    }
}

// Checks with the add_player command if a given player allready
// exists and if not  adds player and scores in to the scoreboard map.
// If the player allready exists updates the players scores.
void add_new_player_and_score
(GAMES &scoreboard, string game_name, string player_name, string player_scores)
{

    // Checks if the named game allready exists
    if(scoreboard.find(game_name) != scoreboard.end())
    {

        // Checks if the named player allready exists
        if(scoreboard.at(game_name).find(player_name)
                == scoreboard.at(game_name).end())
        {
            // If not adds player and scores to the named game
            scoreboard.at(game_name).insert({player_name, stoi(player_scores)});
        }

        else
        {
            // If the player allready exist updates the player's scores
            scoreboard.at(game_name).at(player_name) = stoi(player_scores);

        }

            cout << PLAYER_WAS_ADDED_TEXT << endl;
    }

    else
    {
        cout << GAME_NOT_FOUND_TEXT << endl;
    }
}

// Checks if the named player is in the scoreboard and if is
// removes the player at remove command
void remove_player(GAMES &scoreboard, string player_name)
{
    bool player_found = false;

    for(auto & outer_map_pair : scoreboard)
    {
        // Checks if player exists each games in data structure
        if(outer_map_pair.second.find(player_name)
           != outer_map_pair.second.end())
        {
            // and if does removes player
            outer_map_pair.second.erase(player_name);
            player_found = true;
        }
    }

    if(!player_found)
    {
        cout << PLAYER_NOT_FOUND_TEXT << endl;
    }

    else
    {
        cout << PLAYER_WAS_REMOVED_TEXT << endl;
    }
}
int main()
{
    // data structure
    // game -> player -> points
    GAMES scoreboard;


    // reads file name
    if (!read_file_input(scoreboard))
    {
        return EXIT_FAILURE;
    }

    string user_input = ("");
    string player_name = ("");
    vector<string> parts;

    // Prompts the user for a command.
    while(true)
    {
        cout << "games> ";
        getline(cin, user_input);
        if(user_input.empty())
        {
            cout << INVALID_INPUT_TEXT << endl;
        }

        else
        {
            // Divides users input to parts using split funktion
            parts = split(user_input, ' ');
            user_input = parts.at(0);
            transform(user_input.begin(),
                      user_input.end(),
                      user_input.begin(), ::toupper);

            // Refers to the function to which the command applies.
            if(user_input == "QUIT")
            {
                break;
            }

            else if(user_input == "ALL_GAMES" && parts.size() >=1)
            {
                print_all_games(scoreboard);
            }

            else if(user_input == "GAME" && parts.size() >= 2)
            {
                print_players_and_scores (scoreboard, parts.at(1));
            }

            else if(user_input == "ALL_PLAYERS" && parts.size() >=1)
            {
                print_all_players(scoreboard);
            }

            else if(user_input == "PLAYER" && parts.size() >=2)
            {
                print_named_player_games(scoreboard, parts.at(1));
            }

            else if(user_input == "ADD_GAME" && parts.size() >=2)
            {
                add_new_game(scoreboard, parts.at(1));
            }

            else if(user_input == "ADD_PLAYER" && parts.size() >=4)
            {
                add_new_player_and_score
                        (scoreboard, parts.at(1), parts.at(2), parts.at(3));
            }

            else if(user_input == "REMOVE" && parts.size() >=2)
            {
                remove_player(scoreboard, parts.at(1));
            }


            else
            {
            cout << INVALID_INPUT_TEXT << endl;
            }
            }
    }


    return EXIT_SUCCESS;
}
