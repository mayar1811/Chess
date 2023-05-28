#include <SFML/Graphics.hpp>
#include <iostream>
#include "utilityBox.h"
#include "save.h"
#include <fstream>
#include "Chess.h"
//#include "Boards.h"

using namespace sf;
using namespace std;

Chess AI;

int spritepositions[64]={
    0,1,2,3,4,5,6,7,
    8,9,10,11,12,13,14,15,
    64,64,64,64,64,64,64,64,
    64,64,64,64,64,64,64,64,
    64,64,64,64,64,64,64,64,
    64,64,64,64,64,64,64,64,
    48,49,50,51,52,53,54,55,
    56,57,58,59,60,61,62,63};


class ChessBoard{
  private:
    const float WIDTH = 650;
    const float HEIGTH = 650;
  public:
    void loadtextures(Texture texture[64]);
    void loadboard(Texture texture[64],RectangleShape rectangle[64],Sprite sprite[64]);
    void MainFunctions(int u);
  
};

void ChessBoard::loadtextures(Texture texture[64]){
    for(int i=0;i<64;i++){
      if(spritepositions[i]==0 || spritepositions[i]==7)
        texture[i].loadFromFile("images/icons8-rook-50.png");
      if(spritepositions[i]==1 || spritepositions[i]==6)
        texture[i].loadFromFile("images/icons8-knight-50.png");
      if(spritepositions[i]==2 || spritepositions[i]==5)
        texture[i].loadFromFile("images/icons8-bishop-50.png");
      if(spritepositions[i]==3)
        texture[i].loadFromFile("images/icons8-queen-50.png");
      if(spritepositions[i]==4)
        texture[i].loadFromFile("images/icons8-king-50.png");
      if(spritepositions[i]>=8 and spritepositions[i]<=15)
        texture[i].loadFromFile("images/icons8-pawn-50.png");
      if(spritepositions[i]==63 || spritepositions[i]==56)
        texture[i].loadFromFile("images/w_rook.png");
      if(spritepositions[i]==62 || spritepositions[i]==57)
         texture[i].loadFromFile("images/w_knight.png");
      if(spritepositions[i]==61 || spritepositions[i]==58)
         texture[i].loadFromFile("images/w_bishop.png");
      if(spritepositions[i]==59)
         texture[i].loadFromFile("images/w_queen.png");
      if(spritepositions[i]==60)
         texture[i].loadFromFile("images/w_king.png");
      if(spritepositions[i]>=48 and spritepositions[i]<=55)
         texture[i].loadFromFile("images/w_pawn.png");     
    }
  }
void ChessBoard::loadboard(Texture texture[64],RectangleShape rectangle[64],Sprite sprite[64]){
    for(int j=0;j<64;j++){
        sprite[j].setTexture(texture[j]);
        sprite[j].setScale(1.7f,1.7f);
    }
   for (int j = 0; j < 64; ++j)
    {
        rectangle[j].setSize(sf::Vector2f(WIDTH/8.0f, HEIGTH/8.0f));
    }
    int counter=0;
    for (int i = 0; i < 8; ++i)
    {
      for (int j = 0; j < 8; ++j)
      {
        rectangle[counter].setPosition(j * rectangle[counter].getSize().y, i * rectangle[counter].getSize().x);  ///x,y
        sprite[counter].setPosition(j * rectangle[counter].getSize().y, i * rectangle[counter].getSize().x);
        if((i+j) % 2 == 0)
          rectangle[counter].setFillColor(sf::Color(196, 164, 132));
        else
            rectangle[counter].setFillColor(sf::Color(101, 53, 15));
        counter++;
      }
    }
  }
void ChessBoard::MainFunctions(int u)
  {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGTH), "Chess The Game Of Kings!");
    sf::RectangleShape rectangle[64];
    sf::Texture texture[65];
    sf::Sprite sprite[65];
    loadtextures(texture);
    loadboard(texture,rectangle,sprite);
    Identity box;
    bool isMove;
    float dx=0,dy=0;
    Vector2f oldPos,newPos;
    int n;
    int cc,turn=1;
    int alience,position;
    Vector2f firstpos,secondpos;
    int v;int q[64];
    static int cap=0;
    for (int j = 0; j < 64; ++j)
      q[j]=64;
    while (window.isOpen())
    {
        Vector2i pos = Mouse::getPosition(window);
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                save s;
                window.close();
                if (s.smain()) {
                    ofstream out, out2;
                    out.open("spritepositions.txt");
                    out2.open("boardpositions.txt");
                    for (int i = 0; i < 64; i++) {
                        out << spritepositions[i] << ",";
                        out2 << player_board[i] << ",";
                    }
                    out.close();
                    out2.close();
                }
            }
            if (u != 0) {
                //cout << "turn : " << turn << endl;
                if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                    cout << "Player View" << endl;
                    for (int v = 0; v < 64; v++) {
                        if (v % 8 == 0)
                            cout << endl;
                        cout << player_board[v] << " ";
                    }
                    for (int j = 0; j < 64; ++j) {
                        if (turn % 2 != 0 and player_board[j] > 0) {
                            if (rectangle[j].getGlobalBounds().contains(pos.x, pos.y))
                            {
                                n = j;
                                firstpos = rectangle[j].getPosition();
                                v = spritepositions[j];
                                rectangle[n].setFillColor(sf::Color::Red);
                                if (spritepositions[n] != 64)

                                    cap++;
                            }
                        }
                    }

                }
                if (cap != 0)
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                        cout << "play action" << endl;
                        for (int j = 0; j < 64; ++j) {
                            //cout<<box.identifier(n,j,player_board[j],player_board)<<"=identity"<<endl;
                            if (rectangle[j].getGlobalBounds().contains(pos.x, pos.y)) {
                                //if(n==8 and j==16 and player_board[n]==-6){ 
                                isMove = box.identifier(n, j, player_board[n], player_board);//<<"=identity"<<endl;
                                secondpos = rectangle[j].getPosition();
                                int spritepos = spritepositions[n];
                                //cout<<"shaheer"<<endl;
                                if (isMove) {
                                    cout << "dakhalt" << endl;
                                    turn++;
                                    cc = q[j] = spritepositions[j];
                                    if (j != n) {
                                        cout << "set position " << endl;
                                        sprite[spritepos].setPosition(secondpos);
                                        sprite[cc].setPosition(100000000, 100000000);
                                        int suppos = spritepositions[j];
                                        spritepositions[j] = spritepositions[n];
                                        spritepositions[n] = 64;
                                        
                                        if (player_board[j] == 10 || player_board[j] == -10) {
                                            save s;
                                            window.close();
                                            if (s.smain()) {
                                                ofstream out, out2;
                                                out.open("spritepositions.txt");
                                                out2.open("boardpositions.txt");
                                                for (int i = 0; i < 64; i++) {
                                                    out << spritepositions[i] << ",";
                                                    out2 << player_board[i] << ",";
                                                }
                                                out.close();
                                                out2.close();
                                            }
                                        }
                                        if (j <= 63 and j >= 56 and player_board[n] == 1) {
                                            player_board[j] = 6;
                                            board[j / 8][j % 8] = 6;
                                        }
                                        else if (j >= 0 and j <= 7 and player_board[n] == -1) {
                                            player_board[j] = -6;
                                            board[j / 8][j % 8] = -6;
                                        }
                                        else {
                                            player_board[j] = player_board[n];
                                            board[j / 8][j % 8] = board[n / 8][n % 8];
                                            player_board[n] = 0;
                                            board[n / 8][n % 8] = 0;
                                        }
                                        n = j;
                                    }
                                }
                                int counter = 0;
                                for (int i = 0; i < 8; ++i) {
                                    for (int j = 0; j < 8; ++j) {
                                        if ((i + j) % 2 == 0)
                                            rectangle[counter].setFillColor(sf::Color(196, 164, 132));
                                        else
                                            rectangle[counter].setFillColor(sf::Color(101, 53, 15));
                                        counter++;

                                    }

                                }
                           

                            }
                        }
                        cap = 0;
                        cout << "Player view after playing" << endl;
                        for (int v = 0; v < 64; v++) {
                            if (v % 8 == 0)
                                cout << endl;
                            cout << player_board[v] << " ";
                        }
                    }
                window.clear();
                for (int j = 0; j < 64; ++j)
                    window.draw(rectangle[j]);
                for (int j = 0; j < 65; j++) {
                    if (q[j] == 64)
                        window.draw(sprite[j]);
                }

                window.display();
                if (turn % 2 == 0) {
                    cout << "computer is playing" << endl;
                    cout << "turn : "<<turn << endl;
                    string Move = AI.computer_move(4, board);
                    int new_j = 8 * (Move[2] - 48) + (Move[3] - 48);
                    int new_n = 8 * (Move[0] - 48) + (Move[1] - 48);
                    if (player_board[new_j] == 10 || player_board[new_j] == -10) {
                        save s;
                        window.close();
                        if (s.smain()) {
                            ofstream out, out2;
                            out.open("spritepositions.txt");
                            out2.open("boardpositions.txt");
                            for (int i = 0; i < 64; i++) {
                                out << spritepositions[i] << ",";
                                out2 << player_board[i] << ",";
                            }
                            out.close();
                            out2.close();
                        }
                    }
                    board[Move[2] - 48][Move[3] - 48] = player_board[new_n];
                    board[Move[0] - 48][Move[1] - 48] = 0;
                    player_board[new_j] = player_board[new_n];
                    player_board[new_n] = 0;
                    secondpos = rectangle[new_j].getPosition();
                    int spritepos = spritepositions[new_n];
                    cc = q[new_j] = spritepositions[new_j];
                    if (true) {
                        cout << "computer position is setted" << endl;
                        sprite[spritepos].setPosition(secondpos);
                        sprite[cc].setPosition(100000000, 100000000);
                        int suppos = spritepositions[new_j];
                        spritepositions[new_j] = spritepositions[new_n];
                        spritepositions[new_n] = 64;
                    }
                    turn++;
                    cout << "Computer view after playing" << endl;
                    for (int v = 0; v < 8; v++) {
                        for (int w = 0; w < 8; w++) {
                            cout << board[v][w] << " ";
                        }
                        cout << endl;
                    }
                    cout << endl;
                   
                }
            }

            window.clear();
            for (int j = 0; j < 64; ++j)
                window.draw(rectangle[j]);
            for (int j = 0; j < 65; j++) {
                if (q[j] == 64)
                    window.draw(sprite[j]);
            }

            window.display();
        }
    }
}
