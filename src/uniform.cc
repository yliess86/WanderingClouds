#include "../include/uniform.h"

void Uniform1i::SetValue(int    value) { glUniform1i (ID, value);    }
void Uniform1f::SetValue(float  value) { glUniform1f (ID, value);    }
void Uniform2f::SetValue(float* value) { glUniform2fv(ID, 1, value); }
void Uniform3f::SetValue(float* value) { glUniform3fv(ID, 1, value); }
