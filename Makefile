MyProject : game.o game.c
  gcc game.o -o game
  ./a.exe
MyProject : game.c
  gcc -c game.c -o game.o
installemsdk: 
  cd .. && git clone https://github.com/emscripten-core/emsdk.git
  cd ../emsdk && emsdk install latest && emsdk activate latest && emsdk_env.bat && emcc game.c -s WASM=1 -o game.html
  npm i http-server -g
runserver:
    cd ../emrun game.html
