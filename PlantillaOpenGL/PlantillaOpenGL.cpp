#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>

#define GLEW_STATIC

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <iostream>

using namespace std;

#pragma region Declaración de variables.
GLFWwindow *window;

GLdouble xMarcos = -0.8f;
GLdouble yMarcos = -0.6f;
GLdouble velocidadMarcos = 1.0f;

GLdouble velocidad = 1.5f;
GLdouble velocidadEnemigo = 0.8f;
GLfloat velocidadActual = -0.6f;

float xSol = -0.7f;
float ySol = 0.6f;

GLdouble tiempoAnterior = 0.0;
GLdouble tiempoActual = 0.0;
GLdouble tiempoDiferencial = 0.0;
GLdouble tiempoCambioEscenario = 0.0;

bool reinicio = false;
int contadorbrincos = 0;

enum Direccion { Izquierda, Derecha, Arriba, Abajo };
Direccion direccionBolita = Direccion::Izquierda;
Direccion direccionBolita2 = Direccion::Arriba;
#pragma endregion

#pragma region Escenario.
void sol()
{
	//sol
	glBegin(GL_POLYGON);
	glColor3f(1, .8, 0);
	for (int i = 0; i < 360; i++) {
		glVertex3f(0.2*cos((double)i*3.14159 / 180.0) + xSol, 0.3* sin((double)i*3.14159 / 180.0) + ySol, 0.3);
	}
	glEnd();
}

void sueloVerde() {
	glBegin(GL_POLYGON);
	glColor3f(0.035, 0.57, 0.26);
	glVertex3f(-1.0f, -0.5f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);
	glVertex3f(1.0f, -0.5f, 0.0f);
	glEnd();
}

void sueloDesierto() {
	glBegin(GL_POLYGON);

	glColor3f(0.82, 0.58, 0.17);
	glVertex3f(-1.0f, -0.5f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);
	glVertex3f(1.0f, -0.5f, 0.0f);
	glEnd();
}

void sueloNevado() {
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glVertex3f(-1.0f, -0.5f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);
	glVertex3f(1.0f, -0.5f, 0.0f);
	glEnd();
}

void dibujarEscenarioDia() {
	//Cielo
	glBegin(GL_POLYGON);
	glColor3f(0.05f, 0.88f, 0.92f);
	glVertex3f(-1.0f, -0.51, 1.0f);
	glVertex3f(1.0f, -0.51, 1.0f);
	glVertex3f(1.0f, 1.0, 1.0f);
	glVertex3f(-1.0f, 1.0, 1.0f);
	glEnd();

	//Nubes
	glBegin(GL_POLYGON);
	glColor3f(.85, .82, .82);
	for (int i = 0; i < 360; i++) {
		glVertex3f(0.2*cos((double)i*3.14159 / 180.0) + 0, 0.1* sin((double)i*3.14159 / 180.0) + 0.6, 0);
	}
	for (int i = 0; i < 360; i++) {
		glVertex3f(0.2*cos((double)i*3.14159 / 180.0) + 0.15, 0.1* sin((double)i*3.14159 / 180.0) + 0.6, 0);
	}
	for (int i = 0; i < 360; i++) {
		glVertex3f(0.2*cos((double)i*3.14159 / 180.0) + 0.2, 0.1* sin((double)i*3.14159 / 180.0) + 0.5, 0);
	}
	for (int i = 0; i < 360; i++) {
		glVertex3f(0.2*cos((double)i*3.14159 / 180.0) + 0.2, 0.1* sin((double)i*3.14159 / 180.0) + 0.7, 0);
	}
	for (int i = 0; i < 360; i++) {
		glVertex3f(0.2*cos((double)i*3.14159 / 180.0) + 0.4, 0.1* sin((double)i*3.14159 / 180.0) + 0.6, 0);
	}
	glEnd();

}

void dibujarEscenarioTarde() {
	//Cielo
	glBegin(GL_POLYGON);
	glColor3f(0.92f, 0.49f, 0.11f);
	glVertex3f(-1.0f, -0.51, 1.0f);
	glVertex3f(1.0f, -0.51, 1.0f);
	glVertex3f(1.0f, 1.0, 1.0f);
	glVertex3f(-1.0f, 1.0, 1.0f);
	glEnd();
}

void dibujarEscenarioNoche() {

	//Cielo
	glBegin(GL_POLYGON);
	glColor3f(0.04f, 0.08f, 0.15f);
	glVertex3f(-1.0f, -0.51, 1.0f);
	glVertex3f(1.0f, -0.51, 1.0f);
	glVertex3f(1.0f, 1.0, 1.0f);
	glVertex3f(-1.0f, 1.0, 1.0f);
	glEnd();

	//Luna
	glBegin(GL_POLYGON);
	glColor3f(0.89f, .90f, 0.92f);
	for (int i = 0; i < 360; i++) {
		glVertex3f(0.25*cos((double)i*3.14159 / 180.0) - 0.7, 0.3* sin((double)i*3.14159 / 180.0) + 0.6, 0.3);
	}
	glEnd();

	//Estrellas
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-0.3f, 0.7f, 0.0f);
	glVertex3f(-0.3f, 0.68f, 0.0f);
	glVertex3f(-0.32f, 0.68f, 0.0f);
	glVertex3f(-0.32f, 0.7f, 0.0f);
	glVertex3f(-0.3f, 0.7f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(0.2f, 0.75f, 0.0f);
	glVertex3f(0.2f, 0.73f, 0.0f);
	glVertex3f(0.22f, 0.73f, 0.0f);
	glVertex3f(0.22f, 0.75f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(0.8f, 0.75f, 1.0f);
	glVertex3f(0.8f, 0.73f, 1.0f);
	glVertex3f(0.78f, 0.73f, 1.0f);
	glVertex3f(0.78f, 0.75f, 1.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(0.0f, 0.3f, 1.0f);
	glVertex3f(0.0f, 0.28f, 1.0f);
	glVertex3f(0.02f, 0.28f, 1.0f);
	glVertex3f(0.02f, 0.3f, 1.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(0.5f, 0.3f, 1.0f);
	glVertex3f(0.5f, 0.28f, 1.0f);
	glVertex3f(0.48f, 0.28f, 1.0f);
	glVertex3f(0.48f, 0.3f, 1.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-0.8f, 0.0f, 1.0f);
	glVertex3f(-0.8f, -0.02f, 1.0f);
	glVertex3f(-0.78f, -0.02f, 1.0f);
	glVertex3f(-0.78f, 0.0f, 1.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-0.4f, -0.05f, 1.0f);
	glVertex3f(-0.4f, -0.03f, 1.0f);
	glVertex3f(-0.38f, -0.03f, 1.0f);
	glVertex3f(-0.38f, -0.05f, 1.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(0.2f, -0.07f, 1.0f);
	glVertex3f(0.2f, -0.09f, 1.0f);
	glVertex3f(0.22f, -0.09f, 1.0f);
	glVertex3f(0.22f, -0.07f, 1.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(0.7f, -0.05f, 1.0f);
	glVertex3f(0.7f, -0.07f, 1.0f);
	glVertex3f(0.72f, -0.07f, 1.0f);
	glVertex3f(0.72f, -0.05f, 1.0f);
	glEnd();
}
#pragma endregion

void dibujarMarco() {
	glPushMatrix();
	glTranslatef(xMarcos, yMarcos, 0.0f);
	glScalef(0.6f, 0.6f, 0.0f);
	glPointSize(10.5);
	glBegin(GL_POINTS);
	//Pierna izquierda
	glColor3f(1.0f, 0.8f, 0.6f);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(-0.02f, 0.0f);
	glVertex2f(0.02f, 0.0f);
	glVertex2f(0.02f, 0.02f);
	glVertex2f(0.04f, 0.02f);
	glVertex2f(0.04f, 0.00f);
	glVertex2f(0.00f, 0.02f);
	glVertex2f(0.00f, 0.04f);
	glVertex2f(0.02f, 0.04f);

	//Patineta
	glColor3f(0.0f, 0.53f, 1.0f);
	glVertex2f(-0.08f, 0.0f);
	glVertex2f(-0.06f, -0.02f);
	glVertex2f(-0.04f, -0.02f);
	glVertex2f(-0.02f, -0.02f);
	glVertex2f(0.0f, -0.02f);
	glVertex2f(0.02f, -0.02f);
	glVertex2f(0.04f, -0.02f);
	glVertex2f(0.06f, -0.02f);
	glVertex2f(0.08f, -0.02f);
	glVertex2f(0.1f, -0.02f);
	glVertex2f(0.12f, -0.02f);
	glVertex2f(0.14f, -0.02f);
	glVertex2f(0.16f, -0.02f);
	glVertex2f(0.18f, -0.02f);
	glVertex2f(0.2f, -0.02f);
	glVertex2f(0.22f, -0.02f);
	glVertex2f(0.24f, -0.02f);
	glVertex2f(0.26f, -0.02f);
	glVertex2f(0.28f, -0.02f);
	glVertex2f(0.3f, 0.0f);
	//Ruedas
	glColor3f(0.20f, 0.7f, 0.85f);
	glVertex2f(0.18f, -0.04f);
	glVertex2f(0.2f, -0.04f);
	glVertex2f(0.2f, -0.06f);
	glVertex2f(0.18f, -0.06f);

	glVertex2f(0.0f, -0.04f);
	glVertex2f(0.02f, -0.04f);
	glVertex2f(0.02f, -0.06f);
	glVertex2f(0.0f, -0.06f);

	//Pantalon
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(0.04f, 0.04f);
	glVertex2f(0.04f, 0.06f);
	glVertex2f(0.02f, 0.06f);
	glVertex2f(0.00f, 0.06f);
	glVertex2f(0.00f, 0.08f);
	glVertex2f(0.02f, 0.08f);
	glVertex2f(0.04f, 0.08f);
	glVertex2f(0.02f, 0.1f);
	glVertex2f(0.04f, 0.1f);

	glVertex2f(0.06f, 0.1f);
	glVertex2f(0.08f, 0.1f);
	glVertex2f(0.1f, 0.1f);
	glVertex2f(0.1f, 0.08f);
	glVertex2f(0.12f, 0.08f);
	glVertex2f(0.14f, 0.08f);
	glVertex2f(0.16f, 0.1f);
	glVertex2f(0.18f, 0.12f);
	glVertex2f(0.2f, 0.12f);
	glVertex2f(0.22f, 0.1f);
	glVertex2f(0.24f, 0.08f);
	glVertex2f(0.22f, 0.12f);
	glVertex2f(0.22f, 0.14f);
	glVertex2f(0.2f, 0.14f);
	glVertex2f(0.18f, 0.14f);
	glVertex2f(0.16f, 0.14f);
	glVertex2f(0.16f, 0.12f);
	glVertex2f(0.14f, 0.1f);
	glVertex2f(0.12f, 0.1f);
	glVertex2f(0.14f, 0.12f);
	glVertex2f(0.12f, 0.12f);
	glVertex2f(0.1f, 0.12f);
	glVertex2f(0.08f, 0.12f);
	glVertex2f(0.06f, 0.12f);
	glVertex2f(0.04f, 0.12f);
	glVertex2f(0.02f, 0.12f);
	glVertex2f(0.02f, 0.14f);
	glVertex2f(0.04f, 0.14f);
	glVertex2f(0.06f, 0.14f);
	glVertex2f(0.08f, 0.14f);
	glVertex2f(0.1f, 0.14f);
	glVertex2f(0.12f, 0.14f);
	glVertex2f(0.14f, 0.14f);
	glVertex2f(0.1f, 0.16f);
	glVertex2f(0.08f, 0.16f);
	glVertex2f(0.06f, 0.16f);
	glVertex2f(0.04f, 0.16f);
	glVertex2f(0.22f, 0.08f);
	glVertex2f(0.2f, 0.08f);
	glVertex2f(0.2f, 0.1f);
	glVertex2f(0.18f, 0.1f);
	glVertex2f(0.18f, 0.1f);
	glVertex2f(0.18f, 0.08f);
	glVertex2f(0.16f, 0.08f);
	glVertex2f(0.16f, 0.06f);
	glVertex2f(0.18f, 0.06f);
	glVertex2f(0.2f, 0.06f);
	glVertex2f(0.22f, 0.06f);
	glVertex2f(0.22f, 0.04f);
	glVertex2f(0.2f, 0.04f);
	glVertex2f(0.18f, 0.04f);
	glVertex2f(0.16f, 0.04f);
	glVertex2f(0.16f, 0.02f);

	glColor3f(1.0f, 0.8f, 0.7f);
	glVertex2f(0.18f, 0.02f);
	glVertex2f(0.2f, 0.02f);
	glVertex2f(0.22f, 0.02f);
	glVertex2f(0.24f, 0.02f);
	glVertex2f(0.24f, 0.00f);
	glVertex2f(0.22f, 0.00f);
	glVertex2f(0.2f, 0.00f);
	glVertex2f(0.18f, 0.00f);
	glVertex2f(0.16f, 0.00f);

	glVertex2f(0.04f, 0.18f);
	glVertex2f(0.06f, 0.18f);
	glVertex2f(0.08f, 0.18f);
	glVertex2f(0.1f, 0.18f);
	glVertex2f(0.12f, 0.18f);
	glVertex2f(0.12f, 0.16f);
	glVertex2f(0.14f, 0.16f);
	glVertex2f(0.16f, 0.16f);
	glVertex2f(0.18f, 0.16f);
	glVertex2f(0.2f, 0.16f);
	glVertex2f(0.2f, 0.18f);
	glVertex2f(0.18f, 0.18f);
	glVertex2f(0.16f, 0.18f);
	glVertex2f(0.14f, 0.18f);
	glVertex2f(0.2f, 0.2f);
	glVertex2f(0.18f, 0.2f);
	glVertex2f(0.16f, 0.2f);
	glVertex2f(0.14f, 0.2f);
	glVertex2f(0.12f, 0.2f);
	glVertex2f(0.1f, 0.2f);
	glVertex2f(0.08f, 0.2f);
	glVertex2f(0.06f, 0.2f);
	glVertex2f(0.04f, 0.2f);
	glVertex2f(0.04f, 0.22f);
	glVertex2f(0.06f, 0.22f);
	glVertex2f(0.08f, 0.22f);
	glVertex2f(0.1f, 0.22f);
	glVertex2f(0.12f, 0.22f);
	glVertex2f(0.14f, 0.22f);
	glVertex2f(0.16f, 0.22f);
	glVertex2f(0.18f, 0.22f);
	glVertex2f(0.2f, 0.22f);
	glVertex2f(0.22f, 0.22f);
	glVertex2f(0.24f, 0.22f);
	glVertex2f(0.26f, 0.2f);
	glVertex2f(0.28f, 0.2f);
	glVertex2f(0.3f, 0.18f);
	glVertex2f(0.3f, 0.2f);
	glVertex2f(0.3f, 0.22f);
	glVertex2f(0.32f, 0.22f);
	glVertex2f(0.28f, 0.22f);
	glVertex2f(0.26f, 0.22f);
	glVertex2f(0.3f, 0.24f);
	glVertex2f(0.28f, 0.24f);
	glVertex2f(0.26f, 0.24f);
	glVertex2f(0.24f, 0.24f);
	glVertex2f(0.22f, 0.24f);
	glVertex2f(0.2f, 0.24f);
	glVertex2f(0.2f, 0.26f);
	glVertex2f(0.22f, 0.26f);
	glVertex2f(0.24f, 0.26f);
	glVertex2f(0.26f, 0.26f);
	glVertex2f(0.32f, 0.2f);
	glVertex2f(0.32f, 0.22f);

	glVertex2f(0.24f, 0.26f);
	glVertex2f(0.24f, 0.24f);
	glVertex2f(0.22f, 0.24f);
	glVertex2f(0.2f, 0.24f);
	glVertex2f(0.18f, 0.24f);
	glVertex2f(0.16f, 0.24f);
	glVertex2f(0.14f, 0.24f);
	glVertex2f(0.12f, 0.24f);
	glVertex2f(0.1f, 0.24f);
	glVertex2f(0.08f, 0.24f);
	glVertex2f(0.06f, 0.24f);
	glVertex2f(0.04f, 0.24f);
	glVertex2f(0.18f, 0.26f);
	glVertex2f(0.16f, 0.26f);
	glVertex2f(0.14f, 0.26f);
	glVertex2f(0.12f, 0.26f);
	glVertex2f(0.1f, 0.26f);
	glVertex2f(0.08f, 0.26f);
	glVertex2f(0.06f, 0.26f);
	glVertex2f(0.04f, 0.26f);

	glVertex2f(0.02f, 0.26f);
	glVertex2f(0.00f, 0.26f);
	glVertex2f(-0.02f, 0.24f);
	glVertex2f(-0.04f, 0.24f);
	glVertex2f(-0.04f, 0.22f);
	glVertex2f(-0.04f, 0.2f);
	glVertex2f(-0.06f, 0.2f);
	glVertex2f(-0.04f, 0.18f);
	glVertex2f(-0.06f, 0.18f);
	glVertex2f(-0.08f, 0.18f);
	glVertex2f(-0.08f, 0.2f);
	glVertex2f(-0.06f, 0.22f);
	glVertex2f(-0.06f, 0.24f);
	glVertex2f(-0.06f, 0.26f);
	glVertex2f(-0.04f, 0.26f);
	glVertex2f(-0.02f, 0.26f);
	glVertex2f(-0.04f, 0.28f);
	glVertex2f(-0.02f, 0.28f);
	glVertex2f(0.0f, 0.28f);
	glVertex2f(-0.02f, 0.2f);

	glVertex2f(0.02f, 0.28f);
	glVertex2f(0.04f, 0.28f);
	glVertex2f(0.06f, 0.28f);
	glVertex2f(0.08f, 0.28f);
	glVertex2f(0.1f, 0.28f);
	glVertex2f(0.12f, 0.28f);
	glVertex2f(0.14f, 0.28f);
	glVertex2f(0.16f, 0.28f);
	glVertex2f(0.18f, 0.28f);
	glVertex2f(0.2f, 0.28f);
	glVertex2f(0.22f, 0.28f);

	glVertex2f(0.16f, 0.3f);
	glVertex2f(0.14f, 0.3f);
	glVertex2f(0.12f, 0.3f);
	glVertex2f(0.1f, 0.3f);
	glVertex2f(0.08f, 0.3f);

	glVertex2f(0.06f, 0.32f);
	glVertex2f(0.04f, 0.34f);
	glVertex2f(0.02f, 0.36f);
	glVertex2f(0.02f, 0.38f);
	glVertex2f(0.02f, 0.4f);
	glVertex2f(0.02f, 0.42f);
	glVertex2f(0.04f, 0.44f);
	glVertex2f(0.06f, 0.46f);
	glVertex2f(0.08f, 0.48f);
	glVertex2f(0.1f, 0.48f);
	glVertex2f(0.12f, 0.48f);
	glVertex2f(0.14f, 0.48f);
	glVertex2f(0.16f, 0.48f);
	glVertex2f(0.18f, 0.46f);
	glVertex2f(0.2f, 0.44f);
	glVertex2f(0.22f, 0.42f);
	glVertex2f(0.22f, 0.4f);
	glVertex2f(0.22f, 0.38f);
	glVertex2f(0.22f, 0.36f);
	glVertex2f(0.2f, 0.34f);
	glVertex2f(0.18f, 0.32f);

	glVertex2f(0.16f, 0.32f);
	glVertex2f(0.14f, 0.32f);
	glVertex2f(0.12f, 0.32f);
	glVertex2f(0.1f, 0.32f);
	glVertex2f(0.08f, 0.32f);
	glVertex2f(0.06f, 0.34f);
	glVertex2f(0.08f, 0.34f);
	glVertex2f(0.1f, 0.34f);
	glVertex2f(0.12f, 0.34f);
	glVertex2f(0.14f, 0.34f);
	glVertex2f(0.16f, 0.34f);
	glVertex2f(0.18f, 0.34f);
	glVertex2f(0.04f, 0.36f);
	glVertex2f(0.06f, 0.36f);
	glVertex2f(0.08f, 0.36f);
	glVertex2f(0.1f, 0.36f);
	glVertex2f(0.12f, 0.36f);
	glVertex2f(0.14f, 0.36f);
	glVertex2f(0.16f, 0.36f);
	glVertex2f(0.18f, 0.36f);
	glVertex2f(0.2f, 0.36f);
	glVertex2f(0.04f, 0.38f);
	glVertex2f(0.06f, 0.38f);
	glVertex2f(0.08f, 0.38f);
	glVertex2f(0.1f, 0.38f);
	glVertex2f(0.12f, 0.38f);
	glVertex2f(0.14f, 0.38f);
	glVertex2f(0.16f, 0.38f);
	glVertex2f(0.18f, 0.38f);
	glVertex2f(0.2f, 0.38f);
	glVertex2f(0.04f, 0.4f);
	glVertex2f(0.06f, 0.4f);
	glVertex2f(0.08f, 0.4f);
	glVertex2f(0.1f, 0.4f);
	glVertex2f(0.12f, 0.4f);
	glVertex2f(0.14f, 0.4f);
	glVertex2f(0.16f, 0.4f);
	glVertex2f(0.18f, 0.4f);
	glVertex2f(0.2f, 0.4f);
	glVertex2f(0.04f, 0.42f);
	glVertex2f(0.06f, 0.42f);
	glVertex2f(0.08f, 0.42f);
	glVertex2f(0.1f, 0.42f);
	glVertex2f(0.12f, 0.42f);
	glVertex2f(0.14f, 0.42f);
	glVertex2f(0.16f, 0.42f);
	glVertex2f(0.18f, 0.42f);
	glVertex2f(0.2f, 0.42f);

	glVertex2f(0.06f, 0.44f);
	glVertex2f(0.08f, 0.44f);
	glVertex2f(0.1f, 0.44f);
	glVertex2f(0.12f, 0.44f);
	glVertex2f(0.14f, 0.44f);
	glVertex2f(0.16f, 0.44f);
	glVertex2f(0.18f, 0.44f);
	glVertex2f(0.16f, 0.46f);
	glVertex2f(0.14f, 0.46f);
	glVertex2f(0.12f, 0.46f);
	glVertex2f(0.1f, 0.46f);
	glVertex2f(0.08f, 0.46f);

	glEnd();

	glPopMatrix();
}

void saltoMarcos() {
	int estadoTeclaArribaMarco = glfwGetKey(window, GLFW_KEY_UP);

	if ((estadoTeclaArribaMarco == GLFW_PRESS || estadoTeclaArribaMarco == GLFW_REPEAT) && contadorbrincos == 0 && (yMarcos >= -0.6f && yMarcos <= 0.0f))
	{
		if (yMarcos <= 0.0f)
		{
			yMarcos += (velocidadMarcos * tiempoDiferencial) * 2;
		}
		if (yMarcos >= 0.0f)
		{
			yMarcos = 0.0f;
			contadorbrincos = 1;
		}

	}
	else
		if (estadoTeclaArribaMarco == GLFW_RELEASE)
		{
			contadorbrincos = 1;
		}
	if (contadorbrincos == 1)
	{
		if (yMarcos >= -0.6f)
		{
			yMarcos -= velocidad * tiempoDiferencial;
		}
		if (yMarcos <= -0.6f)
		{
			yMarcos = -0.6f;
			contadorbrincos = 0;
		}
	}
}

void dibujar() {
	if (tiempoCambioEscenario > 90) tiempoCambioEscenario = 0;

	if (tiempoCambioEscenario <= 20)
	{
		if (tiempoCambioEscenario <= 10) dibujarEscenarioDia();
		else if (tiempoCambioEscenario > 10 && tiempoCambioEscenario <= 20) dibujarEscenarioTarde();
		sol();
		xSol += 0.00005;
		ySol -= 0.00005;
	}
	else if (tiempoCambioEscenario > 20 && tiempoCambioEscenario <= 30)
	{
		dibujarEscenarioNoche();
		xSol = -0.7;
		ySol = 0.6;
	}

	if (tiempoCambioEscenario > 30 && tiempoCambioEscenario <= 50)
	{
		if (tiempoCambioEscenario > 30 && tiempoCambioEscenario <= 40) dibujarEscenarioDia();
		else if (tiempoCambioEscenario > 40 && tiempoCambioEscenario <= 50) dibujarEscenarioTarde();
		sol();
		xSol += 0.00005;
		ySol -= 0.00005;
	}
	else if (tiempoCambioEscenario > 50 && tiempoCambioEscenario <= 60)
	{
		dibujarEscenarioNoche();
		xSol = -0.7;
		ySol = 0.6;
	}

	if (tiempoCambioEscenario > 60 && tiempoCambioEscenario <= 80)
	{
		if (tiempoCambioEscenario > 60 && tiempoCambioEscenario <= 70) dibujarEscenarioDia();
		else if (tiempoCambioEscenario > 70 && tiempoCambioEscenario <= 80) dibujarEscenarioTarde();
		sol();
		xSol += 0.00005;
		ySol -= 0.00005;
	}
	else if (tiempoCambioEscenario > 80 && tiempoCambioEscenario <= 90)
	{
		dibujarEscenarioNoche();
		xSol = -0.7;
		ySol = 0.6;
	}

	if (tiempoCambioEscenario <= 30) sueloVerde();
	else if (tiempoCambioEscenario > 30 && tiempoCambioEscenario <= 60) sueloDesierto();
	else if (tiempoCambioEscenario > 60 && tiempoCambioEscenario <= 90) sueloNevado();

	dibujarMarco();
}

void actualizar() {
	tiempoCambioEscenario = glfwGetTime();
	tiempoActual = glfwGetTime();
	tiempoDiferencial = tiempoActual - tiempoAnterior;
	tiempoAnterior = tiempoActual;

	saltoMarcos();
}

int main()
{
	//Si no se puede inicializar glfw
	//Iniciamos ejecucion
	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}
	//Si se pudo iniciar GLFW
	//entonces inicializamosla ventana
	window = glfwCreateWindow(1024, 768, "Ventana", NULL, NULL);
	//Si nopodemos iniciar la ventana
	//Entonces terminamos ejecucion
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	//Establecemos el contexto
	glfwMakeContextCurrent(window);

	//Una vez establecido el contexto activamos funciones modernas
	glewExperimental = true;
	GLenum errorGlew = glewInit();
	if (errorGlew != GLEW_OK) {
		cout << glewGetErrorString(errorGlew);
	}

	const GLubyte *versionGL = glGetString(GL_VERSION);
	cout << "Version OpenGL: " << versionGL;
	

	//ciclode dibujo (Draw loop)
	while (!glfwWindowShouldClose(window)) {
		//Establecer region de dibujo
		glViewport(0, 0, 1024, 768);
		//Establece el color de borrado
		glClearColor(1, 1, 1, 1);
		//Borramos
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Rutina de dibujo.
		dibujar();
		actualizar();

		//Cambiar los buffers
		glfwSwapBuffers(window);
		//Reconocer si hay entradas
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}