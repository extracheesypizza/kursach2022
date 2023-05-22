cd src/
COPY "SFML\lib\sfml-graphics-2.dll" "../res/"
COPY "SFML\lib\sfml-system-2.dll" "../res/"
COPY "SFML\lib\sfml-window-2.dll" "../res/"
g++ main.cpp Application.cpp AVLTree.cpp Controller.cpp Node.cpp Viewer.cpp -o ../res/AVLTree -I SFML/include -L SFML/lib -lsfml-system -lsfml-graphics -lsfml-window 