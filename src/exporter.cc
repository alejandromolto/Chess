#include "exporter.h"
#include <fstream>
#include <sstream>

bool Exporter::exportGametoFile(Board board, const std::string &filename){

    std::ofstream file(filename, std::ios::out | std::ios::app);
    std::vector<std::vector<int>> history = board.gethistory();

    if (file.is_open())
    {

        // GAME HEADER

        file << "# [GAME]" << "\n";

        std::cout << "EXPORTING" << std::endl;
        std::cout << history.size() << std::endl;

        // Boards
        for (int k = 0; k < static_cast<int>(history.size()); k++)
        {

            int board[8][8];
            int cont = 0;

            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    board[i][j] = history[k][cont++];
                }
            }

            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    if (board[i][j] < 10)
                    {
                        file << 0;
                    }
                    file << board[i][j];
                    if (j < 7)
                    {
                        file << " ";
                    }
                }
                file << "\n";
            }
            file << "\n";
        }

        return true;
        
    }else{
        return false;
    }
}

void Exporter::emptyFile(std::string filename){
    std::ofstream ofs(filename, std::ios::trunc);   
}
