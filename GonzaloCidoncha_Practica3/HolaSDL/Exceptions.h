#pragma once
#include <stdexcept>
#include <SDL.h>
#include <SDL_image.h>
using namespace std;

class ArrowsError : public logic_error {
public:
	ArrowsError(const string& msg) : logic_error(msg) {}
	virtual const char* what() const throw() {
		return "Arrows exception";
	}
};

class SDLError : public ArrowsError {
private:
	int type_;

public:
	SDLError(const string& msg, const int type) : ArrowsError(msg), type_(type) {}
	virtual const char* what() const throw() {
		switch (type_) {
		case 0:
			return "Algo de SDL ha fallado: %s\n", SDL_GetError();
			break;
		case 1:
			return "Alguna imagen ha fallado: %s\n", IMG_GetError();
			break;
		}
	}
};

class FileNotFoundError : public ArrowsError {
private:
	string file_;

public:
	FileNotFoundError(const string& msg, const string file) : ArrowsError(msg), file_(file) {}
	virtual const char* what() const throw() {
		string msg = "El archivo " + file_ + " ha fallado";
		return msg.c_str();
	}
};

class FileFormatError : public ArrowsError {
public:
	FileFormatError(const string& msg) : ArrowsError(msg) {}
	virtual const char* what() const throw() {
		return "El archivo no tiene el formato correcto.\n";
	}
};