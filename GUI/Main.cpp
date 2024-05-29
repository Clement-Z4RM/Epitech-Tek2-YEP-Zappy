/*
** EPITECH PROJECT, 2024
** Epitech-Tek2-YEP-Zappy
** File description:
** Main.cpp
*/

#include <iostream>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <fstream>
#include <vector>
#include <cstdio>
#include <unistd.h>

float theta = 0.0f;
GLuint textureID;

struct Pixel {
    unsigned char r, g, b, a;
};

// Fonction pour charger une image BMP
std::vector<Pixel> loadBMP(const char* filename, int& width, int& height) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        printf("Erreur lors de l'ouverture du fichier : %s\n", filename);
        exit(-1);
    }

    // Lecture de l'en-tête BMP
    file.seekg(18);
    file.read(reinterpret_cast<char*>(&width), sizeof(width));
    file.read(reinterpret_cast<char*>(&height), sizeof(height));
    file.seekg(54); // Aller au début des données d'image

    // Lire les données d'image
    std::vector<Pixel> pixels(width * height);
    file.read(reinterpret_cast<char*>(pixels.data()), sizeof(Pixel) * width * height);

    // Inverser les lignes de l'image (BMP est stocké à l'envers)
    std::vector<Pixel> flippedPixels(width * height);
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            flippedPixels[y * width + x] = pixels[(height - y - 1) * width + x];
        }
    }

    return flippedPixels;
}

void init() {
    int width, height;
    std::vector<Pixel> pixels = loadBMP("sprite.bmp", width, height);

    // Générer une texture OpenGL
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    // Définir les paramètres de la texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // Charger les données de l'image dans la texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());
}

void Display() {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

//    glEnable(GL_TEXTURE_2D);
//    glBindTexture(GL_TEXTURE_2D, textureID);
//
//    // Dessiner la sprite
//    glBegin(GL_QUADS);
//    glTexCoord2f(0.0f, 0.0f); glVertex2f(-0.5f, -0.5f); // Coin inférieur gauche
//    glTexCoord2f(1.0f, 0.0f); glVertex2f(0.5f, -0.5f);  // Coin inférieur droit
//    glTexCoord2f(1.0f, 1.0f); glVertex2f(0.5f, 0.5f);   // Coin supérieur droit
//    glTexCoord2f(0.0f, 1.0f); glVertex2f(-0.5f, 0.5f);  // Coin supérieur gauche
//    glEnd();
//
//    glDisable(GL_TEXTURE_2D);
//
    glPushMatrix();
    glRotatef(theta, 0.0f, 0.0f, 1.0f);
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f); glVertex2f(0.0f, 1.0f);
    glColor3f(0.0f, 1.0f, 0.0f); glVertex2f(0.87f, -0.5f);
    glColor3f(0.0f, 0.0f, 1.0f); glVertex2f(-0.87f, -0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glRotatef(-theta, 0.0f, 0.0f, 1.0f);
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 1.0f, 0.0f); glVertex2f(0.0f, 1.0f);
    glColor3f(0.0f, 1.0f, 1.0f); glVertex2f(0.87f, -0.5f);
    glColor3f(1.0f, 0.0f, 1.0f); glVertex2f(-0.87f, -0.5f);
    glEnd();
    glPopMatrix();

    glutSwapBuffers();
}

void Timer(int value) {
    theta += 1.0f;
    glutPostRedisplay();
    glutTimerFunc(16, Timer, 0); // Approximately 60 FPS
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(256, 256);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("OpenGL Sample");
    init();
    glutDisplayFunc(Display);
    glutTimerFunc(0, Timer, 0);
    glutMainLoop();
    return 0;
}
