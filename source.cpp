#include <fstream>
#include <iostream>
#include <vector>
#include <queue>

typedef std::pair<int, int> coordonate;

void readMatrix(std::vector<std::vector<int>>& mat, int& dim) {
	std::ifstream f("Date.txt");
	f >> dim;
    mat.resize(dim, std::vector<int>(dim, 0));
	for (int i = 0; i < dim; i++)
		for (int j = 0; j < dim; j++)
			f >> mat[i][j];
}

int minMutari(const std::vector<std::vector<int>>& matrice, const int& n) {
    std::queue<coordonate> coada;
    std::vector<std::vector<bool>> vizitat(n, std::vector<bool>(n, false));
    coada.push({ 0, 0 });
    vizitat[0][0] = true;
    int mutari = 0;

    while (!coada.empty()) {
        int size = coada.size();
        while (size--) {
            coordonate curent = coada.front();
            coada.pop();

            int x = curent.first;
            int y = curent.second;
            if (x == n - 1 && y == n - 1) {
                return mutari;
            }

            std::vector<coordonate> directii = { {x - matrice[x][y], y}, {x + matrice[x][y], y}, {x, y - matrice[x][y]}, {x, y + matrice[x][y]} };

            for (const auto& dir : directii) {
                int newX = dir.first;
                int newY = dir.second;

                if (newX >= 0 && newX < n && newY >= 0 && newY < n && !vizitat[newX][newY]) {
                    coada.push({ newX, newY });
                    vizitat[newX][newY] = true;
                }
            }
        }
        mutari++;
    }
    return -1;
}

int main() {
	std::vector<std::vector<int>> matrix;
    int dim;
	readMatrix(matrix,dim);
    int result = minMutari(matrix, dim);
    if (result != -1)
        std::cout << "Numarul minim de mutari: " << result <<"\n";
    else
        std::cout << "Nu exista o cale valida." << "\n";
    return 0;
}
