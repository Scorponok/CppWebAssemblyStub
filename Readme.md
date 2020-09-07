# Getting Started with C++ and WebAssembly on Windows

## 1. Clone this project

```
git clone https://github.com/Scorponok/CppWebAssemblyStub
```

This clones the project into a subfolder of your current folder named "CppWebAssemblyStub".

## 2. Get the Emscripten SDK

This project uses Emscripten. Get the emscripten SDK, as described here: https://emscripten.org/docs/getting_started/downloads.html

Once you've done this, you should have an `emsdk` folder somewhere.

## 3. Run local web server

You would think you could run WebAssembly by loading a web page at a `file://` URL, but web browsers don't seem to be able to do that because that would be too easy. You have to actually run a web server instead. You can run your own web server or use the very simple `runserver.py` script included with this project.

To use the web server started by `runserver.py`:

1. Open a command prompt
2. Run `emsdk\emsdk_env.bat`. This puts a python2 executable in your PATH, which I don't think is necessarily a good idea, but we only need python for this one thing so let's run with it.
3. Switch to the folder containing `runserver.py` and run it using `python runserver.py`. (Note just typing `runserver.py` may not work as it will use some different version of python that may not be what you want, and may not have the right libraries installed.)
4. Leave the web command prompt / web server open as you recompile and update your page.

You can use any other web server, as long as it will serve the page and understands the "wasm" MIME type. Whatever web server you're running, make sure it can't be accessed from the public internet to avoid naughty hackers messing with it.

## 4. Compile your C++ file

Emscripten requires you to generate two output files from your C++ source - a `.wasm` file containing WebAssembly bytecode, and a `.js` file which loads it and interfaces with the DOM. You can compile them as follows:

1. Open another command prompt and run `emsdk\emsdk_env.bat`. This sets up the environment for what you actually want to do, which is compiling C++ into WebAssembly and Javascript.
2. `cd` to the folder with this project in it and compile the `main.cc` file to WebAssembly: `em++ main.cc -o main.wasm --std=c++17`
3. Also, compile the javascript infrastructure for your `main.cc` file: `em++ main.cc -o main.js --std=c++17`

## 5. Load the page

Open `http://localhost:9090/` in your web browser. This should load the index.html page in this folder. You should see numbers counting up on the page - if not, something is wrong.

## 6. Modifying your program

If you change your `main.cc` file, you'll need to regenerate one or both of the `main.wasm` and `main.js` outputs. Generally you need to recompile `main.wasm` if you change the C++ logic; you need to recompile `main.js` if you change any javascript, or possibly if you change the `#include`d headers.

Once you've recompiled, reload `http://localhost:9090/` in your web browser to see the changes. If things don't seem right, check the compiler output and browser console for any issues.

## 7. Useful links

- Emscripten API reference: https://emscripten.org/docs/api_reference/emscripten.h.html
- Emscripten FAQ: https://emscripten.org/docs/getting_started/FAQ.html
