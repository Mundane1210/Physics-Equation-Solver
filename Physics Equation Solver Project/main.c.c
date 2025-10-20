// C Source File
// Created 9/15/2025; 2:49:07 PM

// Delete or comment out the items you do not need.
#define COMMENT_STRING         "Place your comment here."
#define COMMENT_PROGRAM_NAME   "Place your program name here."
#define COMMENT_VERSION_STRING "Place your version string here."
#define COMMENT_VERSION_NUMBER 0,0,0,0 /* major, minor, revision, subrevision */
#define COMMENT_BW_ICON \
	{0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000}
#define COMMENT_GRAY_ICON \
	{0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000}, \
	{0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000}

#include <tigcclib.h>
#include <math.h>
#include <string.h>

#include <stdio.h>

// Define struct for variables
typedef struct 
{
	char name[10];   // variable symbol, e.g. "v", "a", "F"
	char desc[50];   // description, e.g. "velocity"
	char unit[10];   // SI units, e.g. "m/s"
	double value;    // numerical value (user entered)
} Variable;

typedef struct 
{
	char equation[100];
    char variables[10][10];
    int varCount;
}EquationMeta;


//Variables
Variable variables[] = {
    {"t", "time", "s", 0.0},
    {"x", "position", "m", 0.0},
    {"d", "displacement", "m", 0.0},
    {"v", "velocity", "m/s", 0.0},
    {"vi", "initial velocity", "m/s", 0.0},
    {"vf", "final velocity", "m/s", 0.0},
    {"a", "acceleration", "m/s^2", 0.0},
    {"g", "gravitational acceleration", "m/s^2", 9.8},

    {"F", "force", "N", 0.0},
    {"Fx", "force x-component", "N", 0.0},
    {"Fy", "force y-component", "N", 0.0},
    {"N", "normal force", "N", 0.0},
    {"T", "tension", "N", 0.0},
    {"fk", "kinetic friction force", "N", 0.0},
    {"fs", "static friction force", "N", 0.0},
    {"mu_k", "coefficient of kinetic friction", "", 0.0},
    {"mu_s", "coefficient of static friction", "", 0.0},
    {"W", "work", "J", 0.0},
    {"P", "power", "W", 0.0},

    {"m", "mass", "kg", 0.0},
    {"p", "momentum", "kg m/s", 0.0},
    {"I", "moment of inertia", "kg*m^2", 0.0},
    {"L", "angular momentum", "kg*m^2/s", 0.0},
    {"tau", "torque", "N*m", 0.0},
    {"theta", "angular displacement", "rad", 0.0},
    {"omega", "angular velocity", "rad/s", 0.0},
    {"alpha", "angular acceleration", "rad/s^2", 0.0},

    {"KE", "kinetic energy", "J", 0.0},
    {"PE", "potential energy", "J", 0.0},
    {"U_g", "gravitational potential energy", "J", 0.0},
    {"U_s", "spring potential energy", "J", 0.0},
    {"k", "spring constant", "N/m", 0.0},
    {"x_s", "spring displacement", "m", 0.0},

    {"rho", "density", "kg/m^3", 0.0},
    {"p0", "pressure initial", "Pa", 0.0},
    {"p", "pressure", "Pa", 0.0},
    {"dP", "pressure difference", "Pa", 0.0},
    {"V", "volume", "m^3", 0.0},
    {"h", "height", "m", 0.0},

    {"Q", "heat", "J", 0.0},
    {"c", "specific heat capacity", "J/kg*K", 0.0},
    {"dT", "temperature change", "K", 0.0},
    {"T", "temperature", "K", 0.0},
    {"R", "ideal gas constant", "J/mol*K", 8.314},
    {"n", "number of moles", "mol", 0.0},
    {"pV", "pressure*volume", "Pa*m^3", 0.0}
};

//Equations
// ----------------- KINEMATICS -----------------
EquationMeta equations[] = {
    {"vf = vi + a*t", {"vf", "vi", "a", "t"}, 4},
    {"x = x0 + vi*t + 0.5*a*t^2", {"x", "x0", "vi", "t", "a"}, 5},
    {"vf^2 = vi^2 + 2*a*(x - x0)", {"vf", "vi", "a", "x", "x0"}, 5},
    {"d = v*t", {"d", "v", "t"}, 3},
    {"v = (vf + vi)/2", {"v", "vf", "vi"}, 3},

// ----------------- NEWTONS LAWS -----------------
    {"F = m*a", {"F", "m", "a"}, 3},
    {"W = m*g", {"W", "m", "g"}, 3},
    {"fk = mu_k*N", {"fk", "mu_k", "N"}, 3},
    {"fs = mu_s*N", {"fs", "mu_s", "N"}, 3},
    {"N = m*g", {"N", "m", "g"}, 3},

// ----------------- WORK, ENERGY, POWER -----------------
    {"W = F*d", {"W", "F", "d"}, 3},
    {"KE = 0.5*m*vf^2", {"KE", "m", "vf"}, 3},
    {"U_g = m*g*h", {"U_g", "m", "g", "h"}, 4},
    {"U_s = 0.5*k*x_s^2", {"U_s", "k", "x_s"}, 3},
    {"P = W/t", {"P", "W", "t"}, 3},
    {"P = F*v", {"P", "F", "v"}, 3},
    {"PE = KE + U_g + U_s", {"PE", "KE", "U_g", "U_s"}, 4},

// ----------------- MOMENTUM -----------------
    {"p = m*vf", {"p", "m", "vf"}, 3},
    {"J = F*t", {"J", "F", "t"}, 3},
    {"J = p", {"J", "p"}, 2},

// ----------------- ROTATION -----------------
    {"tau = r*F", {"tau", "r", "F"}, 3},
    {"I = m*r^2", {"I", "m", "r"}, 3},
    {"tau = I*alpha", {"tau", "I", "alpha"}, 3},
    {"theta = theta + omega*t + 0.5*alpha*t^2", {"theta", "omega", "alpha", "t"}, 4},
    {"omega = omega + alpha*t", {"omega", "alpha", "t"}, 3},
    {"KE = 0.5*I*omega^2", {"KE", "I", "omega"}, 3},

// ----------------- OSCILLATIONS -----------------
    {"T = 2*pi*sqrt(m/k)", {"T", "m", "k"}, 3},
    {"T = 2*pi*sqrt(L/g)", {"T", "L", "g"}, 3},
    {"f = 1/T", {"f", "T"}, 2},
    {"x = A*cos(omega*t)", {"x", "A", "omega", "t"}, 4},

// ----------------- WAVES -----------------
    {"v = f*lambda", {"v", "f", "lambda"}, 3},
    {"T = 1/f", {"T", "f"}, 2},
    {"I = P/A", {"I", "P", "A"}, 3},

// ----------------- GRAVITY & CIRCULAR MOTION -----------------
    {"Fc = m*vf^2/r", {"Fc", "m", "vf", "r"}, 4},
    {"g = G*m/r^2", {"g", "G", "m", "r"}, 4},
    {"Fg = G*m1*m2/r^2", {"Fg", "G", "m1", "m2", "r"}, 5},
    {"T = 2*pi*r/v", {"T", "r", "v"}, 3}
};

//other variables
bool success = false;


bool isVariableKnown(const char * varName)
{
	for(int i = 0; i < sizeof(variables) / sizeof(variables[0]); i++)
	{
		if(strcmp(variables[i].name, varName) == 0)
		{
			if (variables[i].value != 0.0)
			{
				return true;
			}
		}
	}
	return false;
}

double getVariable(const char * varName)
{
	for(int i = 0; i < sizeof(variables) / sizeof(variables[0]); i++)
	{
		if(strcmp(variables[i].name, varName) == 0)
		{
			return variables[i].value;
		}
	}
	return 0.0;
}

bool setVariable(const char * varName,  double varVal)
{
	for(int i = 0; i < sizeof(variables) / sizeof(variables[0]); i++)
	{
		if(strcmp(variables[i].name, varName) == 0)
		{
			variables[i].value = varVal;
			return true;
		}
	}
	return false;
}

int countUnkowns(EquationMeta * eq)
{
	int unknowns = 0;
	for(int i = 0; i < eq -> varCount; i ++)
	{
		if(!isVariableKnown(eq -> variables[i]))
		{
			unknowns++;
		}
	}
	return unknowns;
}

bool isVariableInEquation(EquationMeta * eq, const char * target)
{
	for(int i = 0; i < eq->varCount; i++)
	{
		if(strcmp(eq->variables[i], target) == 0)
		{
			return true;
		}
	}
	return false;
}

bool solve(EquationMeta * eq, const char * target, EquationMeta * library, int librarySize)
{
	
}


// Main Function
void _main(void)
{
	

}