#ifndef INCLUDED_PERSPECTIVEMATRIX_H
#define INCLUDED_PERSPECTIVEMATRIX_H

class CMatrix44;

CMatrix44 ComputeProjectionMatrix(float FOVDegrees, float fAspectRatio, float fNear, float fFar);


#endif // ifndef INCLUDED_PERSPECTIVEMATRIX_H