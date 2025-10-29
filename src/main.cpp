#include "iostream"
#include <string>

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

#define DEFAULT_LETTER "0"
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
  Separator();
  Space();
  WriteLn("You must find:");
  Space();

  for (size_t i = 0; i < words->length(); i++) {
    if (words[i] != "") {
      bool isLastWord = (i >= (words->length() - 1)) || words[i + 1] == "";
      Write(words[i] + (isLastWord ? "" : ", "));
    }
  }
}

string GetRandomLetter() {

  int randomIndex = rand() % 26;
  char letter = 'A' + randomIndex;
  return string(1, letter);
}


void ConstructBoard(int size, int nOfWords, string words[], string letters[]) {
  int setWords = 0;

  for (size_t i = 0; i < nOfWords; i++) {
    string word = words[i];

    for (size_t j = 0; j < MAX_ATTEMPTS; j++) {
      bool isVertical = rand() % 2;

      if (isVertical) {
        int startRow = rand() % (size - word.length());
        int startCol = rand() % size;

        bool isAvailable = true;
        int currentCell = 0;

        for (size_t k = 0; k < word.length(); k++) {
          currentCell = (startRow + k) * size + startCol;

          if ((letters[currentCell] != "0") && letters[currentCell] != string(1, word[k])) {
            isAvailable = false;
            break;
          }
        }
        if (!isAvailable) continue;
        for (size_t k = 0; k < word.length(); k++) {
          currentCell = (startRow + k) * size + startCol;
          letters[currentCell] = word[k];
        }
        setWords++;
        break;
      } else {
        int startRow = rand() % size;
        int startCol = rand() % (size - word.length());

        bool isAvailable = true;
        int currentCell = 0;

        for (size_t k = 0; k < word.length(); k++) {
          currentCell = startRow * size + startCol + k;

          if ((letters[currentCell] != "0") && letters[currentCell] != string(1, word[k])) {
            isAvailable = false;
            break;
          }
        }
        if (!isAvailable) continue;
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


  for (size_t i = 0; i < MAX_SIZE * MAX_SIZE; i++) {
    if (letters[i] == "0") {
      letters[i] = GetRandomLetter();
    }
  }
}



void RenderBoard(int size, string letters[], string words[]) {

  system("cls");

  for (size_t i = 0; i < size; i++) {
    for (size_t j = 0; j < size; j++) {
      Write(" " + letters[i * size + j]);
    }
    Space();
  }

  Space();
  ShowWords(words);
}



int main() {
  srand(time(0));
  ShowPresentation();

  int size = GetBoardSize();
  int nOfWords = GetnOfWordSearch();
  string words[] = {WORDS};



  bool isWordSelected[MAX_N_WORDS];
  fill(begin(isWordSelected), end(isWordSelected), false);

  string selectedWords[MAX_N_WORDS];
  fill(begin(selectedWords), end(selectedWords), NULL);


  int insertIndex = 0;
  for (size_t i = 0; i < nOfWords; i++) {
    while (!isWordSelected[i]) {
      int newWord = rand() % nOfWords;


      if (words[i].length() > size) continue;

      selectedWords[insertIndex] = words[i];
      isWordSelected[i] = true;
      insertIndex++;
    }
  }



  Space();
  Separator();
  Space();

  string letters[MAX_SIZE * MAX_SIZE];
  fill(begin(letters), end(letters), DEFAULT_LETTER);
  try {

    ConstructBoard(size, nOfWords, selectedWords, letters);
  } catch (...) {
    WriteLn("Max attempts exceded!");
    return 1;
  }

  RenderBoard(size, letters, selectedWords);
}
