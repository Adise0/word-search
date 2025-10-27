#include "iostream";
#include <string>;

using namespace std;

// #region Consts
#define MIN_SIZE 10
#define MAX_SIZE 20

#define MIN_N_WORDS 1
#define MAX_N_WORDS 10

#define MAX_ATTEMPTS 500
#define WORDS                                                                                                                                                                      \
  "MOUNTAIN", "OCEAN", "FOREST", "RIVER", "THUNDER", "LIGHTNING", "DESERT", "VOLCANO", "ISLAND", "GLACIER", "CANYON", "HURRICANE", "TORNADO", "EARTHQUAKE", "LAVA", "CLOUD",       \
      "STORM", "VALLEY", "WIND", "STONE"
// #endregion


// #region Utils
void Write(string input) { cout << input; }
void WriteLn(string input) { cout << input << endl; }
string Ask(string message) {
  cout << message << endl;
  string result;
  getline(cin, result);
  return result;
}
void Space() { WriteLn(""); }
void Separator() { WriteLn("============================="); }
// #endregion

void ShowPresentation() {
  Separator();
  Space();
  WriteLn("        LETTER SOUP");
  Space();
  Separator();
}

int GetBoardSize() {
  // #region GetBoardSize
  Space();
  int size = -1;
  WriteLn("What size we playing on? (" + to_string(MIN_SIZE) + "-" + to_string(MAX_SIZE) + ")");
  while (true) {
    try {
      size = stoi(Ask(""));

      if (size < MIN_SIZE || size > MAX_SIZE) {

        WriteLn("Please input a number between " + to_string(MIN_SIZE) + " and " + to_string(MAX_SIZE));
        continue;
      }
      break;
    } catch (...) {
      WriteLn("Please input a valid number");
    }
  }
  return size;
  // #endregion
}
// TODO: Make single func
int GetnOfWordSearch() {
  // #region GetnOfWordSearch
  Space();
  int nOfWords = -1;
  WriteLn("How many words? (" + to_string(MIN_N_WORDS) + "-" + to_string(MAX_N_WORDS) + ")");
  while (true) {
    try {
      nOfWords = stoi(Ask(""));

      if (nOfWords < MIN_N_WORDS || nOfWords > MAX_N_WORDS) {

        WriteLn("Please input a number between " + to_string(MIN_N_WORDS) + " and " + to_string(MAX_N_WORDS));
        continue;
      }
      break;
    } catch (...) {
      WriteLn("Please input a valid number");
    }
  }
  return nOfWords;
  // #endregion
}

void ShowWords(string words[]) {
  WriteLn("You must find:");
  for (size_t i = 0; i < words->length(); i++) {
    if (words[i] != "") {
      Write(words[i] + ", ");
    }
  }
}

void ConstructBoard(int size, int nOfWords, string words[], string letters[]) {
  bool isOcupied[MAX_SIZE * MAX_SIZE] = {false};
  int setWords = 0;

  for (size_t i = 0; i < nOfWords; i++) {
    string word = words[i];

    for (size_t j = 0; j < MAX_ATTEMPTS; j++) {
      bool isVertical = rand() % 1;

      if (isVertical) {
        int startRow = rand() % size - word.length();
        int startCol = rand() % size;
        bool isFree = true;
        int currentCell = 0;
        for (size_t k = 0; k < word.length(); k++) {
          currentCell = (startRow + k) * size + startCol;

          if (isOcupied[currentCell]) {
            isFree = false;
            break;
          }
        }
        if (!isFree) continue;
        for (size_t k = 0; k < word.length(); k++) {
          currentCell = (startRow + k) * size + startCol;
          letters[currentCell] = word[k];
        }
        setWords++;
        break;
      } else {
        int startRow = rand() % size;
        int startCol = rand() % size - word.length();
        bool isFree = true;
        int currentCell = 0;
        for (size_t k = 0; k < word.length(); k++) {
          currentCell = startRow * size + startCol + k;

          if (isOcupied[currentCell]) {
            isFree = false;
            break;
          }
        }
        if (!isFree) continue;
        for (size_t k = 0; k < word.length(); k++) {
          currentCell = startRow * size + startCol + k;
          letters[currentCell] = word[k];
        }
        setWords++;
        break;
      }
    }
  }
  if (setWords < nOfWords) {
    throw new exception("Max attempts exceded");
  }
}

void RenderBoard(int size, string letters[]) {

  for (size_t i = 0; i < size; i++) {
    for (size_t j = 0; j < size; j++) {
      Write(" " + letters[i * size + j]);
    }
    Space();
  }
}



int main() {
  srand(time(0));
  ShowPresentation();

  int size = GetBoardSize();
  int nOfWords = GetnOfWordSearch();

  string words[] = {WORDS};
  bool isWordSelected[MAX_N_WORDS] = {false};
  string selectedWords[MAX_N_WORDS] = {""};


  int insertIndex = 0;
  for (size_t i = 0; i < nOfWords; i++) {
    while (!isWordSelected[i]) {
      int newWord = rand() % nOfWords;
      isWordSelected[i] = true;
      selectedWords[insertIndex] = words[i];
      insertIndex++;
    }
  }

  ShowWords(selectedWords);

  Space();
  Separator();
  Space();

  string letters[MAX_SIZE * MAX_SIZE] = {"0"};
  ConstructBoard(size, nOfWords, selectedWords, letters);
  RenderBoard(size, letters);
}
