class WordleGame{
private:

    std::vector<std::vector<char>> Board;
    std::string RandomGuess;
    std::string word;
    std::vector<std::string> words;

public:

    void UpdateBoard(std::vector<char> guess, int index){
        this -> Board[index] = std::move(guess);
    }

    void PrintBoard(){
        for(auto & i : Board){
            for(auto & j : i){
                std::cout<<j<<" ";
            }
            std::cout<<std::endl;
        }
    }

    std::vector<std::vector<char>> GetBoard() const { return this -> Board; }

     explicit WordleGame(std::ifstream& file) : Board(6, std::vector<char>(5, '_')){
         std::cout << " WORDLE" << std::endl;
         PrintBoard();

         while(std::getline(file, word)){
             words.emplace_back(word);
         }

         std::srand(static_cast<unsigned int>(std::time(nullptr)));
         int RandomIndex = std::rand() % words.size();
         RandomGuess = words[RandomIndex];
         std::vector<char> RandomGuessVector;
         for(auto & i : RandomGuess){
             RandomGuessVector.push_back(i);
         }


//         std::cout<<"Todays Word: " << RandomGuess;

         int cnt = 0;
         std::vector<char> Try(5);
         std::vector<char>::iterator it;
         while(cnt != 6){
             for(int i = 0; i < 5; i++) {
                 std::cin >> Try[i];
             }

             UpdateBoard(Try, cnt);
             PrintBoard();

             for(int i = 0; i < 5; i++){
                 it = find(RandomGuessVector.begin(), RandomGuessVector.end(), Try[i]);
                 if(Try[i] == RandomGuessVector[i]){
                    std::cout<<Try[i]<<" la pozitia "<<i + 1<<" este verde"<<std::endl;
                 }
                 else if(it != RandomGuessVector.end()){
                     std::cout<<Try[i]<<" la pozitia "<<i + 1<<" este galbena"<<std::endl;
                 }
             }

             if(Try == RandomGuessVector){
                 std::cout<<"You got it in "<<cnt + 1<<" tries!"<<std::endl;
                 break;
             }
             cnt++;

         }
         if(cnt==6){
             std::cout<<"WA WA WA"<<std::endl;
             std::cout<<"Cuvantul era: "<<RandomGuess;
         }
     }


};
