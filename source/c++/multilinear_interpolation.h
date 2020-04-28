#include <vector>

using namespace std;

/* 
 Multilinear interpolation.
 Up to five dimensions.
 These are hard coded. This is relatively easy to read, but not as general as, 
 e.g., https://github.com/parsiad/mlinterp
 This version assumes simple arrays.
 Pass in the number of dimensions for each array, 
    then the grid values for each dimension (arrays),
    then the array of function values at each point,
    then the locations of the desired points in each dimension.
 The grid of function values is mapped to 1-D in row-major form:
    For x,y,z indexed by i,j,k, we have f[i][j][k] ==> f[i*nz*ny + j*nz + k]
 See LI_2D for specific description of values passed.
 LI_3D and LI_4D are tested by comparison of the rcSLW code to the python version.
*/

////////////////////////////////////////////////////////////////////////////////
int get_location_dim(const int nx, const double *x, const double xP) {
    if(xP <= x[0])
        return 0;
    else if(xP >= x[nx-1])
        return nx-2;
    else
        return lower_bound(x, x+nx, xP) - x - 1;
}

////////////////////////////////////////////////////////////////////////////////

double LI_1D(const int nx,
             const double *x,
             const double *f,
             const double xP){

    int i = get_location_dim(nx,x,xP);

    int ip = i+1;

    double xWta = (xP - x[i])/(x[i+1]-x[i]);

    double xWtb = 1-xWta;

    return (f[i ]*xWtb +
            f[ip]*xWta);
}

////////////////////////////////////////////////////////////////////////////////

double LI_2D(const int nx,               // number of points in x
             const int ny,               // number of points in y
             const double *x,            // x grid values
             const double *y,            // y grid values
             const double *f,            // field of function values over the x, y grid (1-D row major)
             const double xP,            // interpolation point in x
             const double yP){           // interpolation point in y

    int i = get_location_dim(nx,x,xP);
    int j = get_location_dim(ny,y,yP);

    int ip = i+1;
    int jp = j+1;

    double xWta = (xP - x[i])/(x[i+1]-x[i]);
    double yWta = (yP - y[j])/(y[j+1]-y[j]);

    double xWtb = 1-xWta;
    double yWtb = 1-yWta;

    return (f[i *ny +j ]*xWtb +                    // return f[i ][j ]*xWtb*yWtb +
            f[ip*ny +j ]*xWta) * yWtb +            //        f[ip][j ]*xWta*yWtb +
           (f[i *ny +jp]*xWtb +                    //        f[i ][jp]*xWtb*yWta +
            f[ip*ny +jp]*xWta) * yWta;             //        f[ip][jp]*xWta*yWta;
}

////////////////////////////////////////////////////////////////////////////////

double LI_3D(const int nx, 
             const int ny,
             const int nz,
             const double *x,
             const double *y,
             const double *z,
             const double *f,
             const double xP,
             const double yP,
             const double zP){

    int i = get_location_dim(nx,x,xP);
    int j = get_location_dim(ny,y,yP);
    int k = get_location_dim(nz,z,zP);

    int ip = i+1;
    int jp = j+1;
    int kp = k+1;

    double xWta = (xP - x[i])/(x[i+1]-x[i]);
    double yWta = (yP - y[j])/(y[j+1]-y[j]);
    double zWta = (zP - z[k])/(z[k+1]-z[k]);

    double xWtb = 1-xWta;
    double yWtb = 1-yWta;
    double zWtb = 1-zWta;

    int nzy = nz*ny;

    return ((f[i *nzy + j *nz + k ]*xWtb +                      // return f[i ][j ][k ]*xWtb*yWtb*zWtb +
             f[ip*nzy + j *nz + k ]*xWta) * yWtb +              //        f[ip][j ][k ]*xWta*yWtb*zWtb +
            (f[i *nzy + jp*nz + k ]*xWtb +                      //        f[i ][jp][k ]*xWtb*yWta*zWtb +
             f[ip*nzy + jp*nz + k ]*xWta) * yWta) * zWtb +      //        f[ip][jp][k ]*xWta*yWta*zWtb +
           ((f[i *nzy + j *nz + kp]*xWtb +                      //        f[i ][j ][kp]*xWtb*yWtb*zWta +
             f[ip*nzy + j *nz + kp]*xWta) * yWtb +              //        f[ip][j ][kp]*xWta*yWtb*zWta +    
            (f[i *nzy + jp*nz + kp]*xWtb +                      //        f[i ][jp][kp]*xWtb*yWta*zWta +
             f[ip*nzy + jp*nz + kp]*xWta) * yWta) * zWta;       //        f[ip][jp][kp]*xWta*yWta*zWta;
}

////////////////////////////////////////////////////////////////////////////////

double LI_4D(const int nx,
             const int ny,
             const int nz,
             const int nw,
             const double *x,
             const double *y,
             const double *z,
             const double *w,
             const double *f,
             const double xP,
             const double yP,
             const double zP,
             const double wP){

    int i = get_location_dim(nx,x,xP);
    int j = get_location_dim(ny,y,yP);
    int k = get_location_dim(nz,z,zP);
    int l = get_location_dim(nw,w,wP);

    int ip = i+1;
    int jp = j+1;
    int kp = k+1;
    int lp = l+1;

    double xWta = (xP - x[i])/(x[i+1]-x[i]);
    double yWta = (yP - y[j])/(y[j+1]-y[j]);
    double zWta = (zP - z[k])/(z[k+1]-z[k]);
    double wWta = (wP - w[l])/(w[l+1]-w[l]);

    double xWtb = 1-xWta;
    double yWtb = 1-yWta;
    double zWtb = 1-zWta;
    double wWtb = 1-wWta;

    int nwzy = nw*nz*ny;
    int nwz  = nw*nz;

    return (((f[i *nwzy + j *nwz + k *nw + l ]*xWtb +                                // return f[i ][j ][k ][l ]*xWtb*yWtb*zWtb*wWtb +
              f[ip*nwzy + j *nwz + k *nw + l ]*xWta) * yWtb +                        //        f[ip][j ][k ][l ]*xWta*yWtb*zWtb*wWtb +
             (f[i *nwzy + jp*nwz + k *nw + l ]*xWtb +                                //        f[i ][jp][k ][l ]*xWtb*yWta*zWtb*wWtb +
              f[ip*nwzy + jp*nwz + k *nw + l ]*xWta) * yWta) * zWtb +                //        f[ip][jp][k ][l ]*xWta*yWta*zWtb*wWtb +
            ((f[i *nwzy + j *nwz + kp*nw + l ]*xWtb +                                //        f[i ][j ][kp][l ]*xWtb*yWtb*zWta*wWtb +
              f[ip*nwzy + j *nwz + kp*nw + l ]*xWta) * yWtb +                        //        f[ip][j ][kp][l ]*xWta*yWtb*zWta*wWtb +    
             (f[i *nwzy + jp*nwz + kp*nw + l ]*xWtb +                                //        f[i ][jp][kp][l ]*xWtb*yWta*zWta*wWtb +
              f[ip*nwzy + jp*nwz + kp*nw + l ]*xWta) * yWta) * zWta) * wWtb +        //        f[ip][jp][kp][l ]*xWta*yWta*zWta*wWtb +
           (((f[i *nwzy + j *nwz + k *nw + lp]*xWtb +                                //        f[i ][j ][k ][lp]*xWtb*yWtb*zWtb*wWta +
              f[ip*nwzy + j *nwz + k *nw + lp]*xWta) * yWtb +                        //        f[ip][j ][k ][lp]*xWta*yWtb*zWtb*wWta +
             (f[i *nwzy + jp*nwz + k *nw + lp]*xWtb +                                //        f[i ][jp][k ][lp]*xWtb*yWta*zWtb*wWta +
              f[ip*nwzy + jp*nwz + k *nw + lp]*xWta) * yWta) * zWtb +                //        f[ip][jp][k ][lp]*xWta*yWta*zWtb*wWta +
            ((f[i *nwzy + j *nwz + kp*nw + lp]*xWtb +                                //        f[i ][j ][kp][lp]*xWtb*yWtb*zWta*wWta +
              f[ip*nwzy + j *nwz + kp*nw + lp]*xWta) * yWtb +                        //        f[ip][j ][kp][lp]*xWta*yWtb*zWta*wWta +    
             (f[i *nwzy + jp*nwz + kp*nw + lp]*xWtb +                                //        f[i ][jp][kp][lp]*xWtb*yWta*zWta*wWta +
              f[ip*nwzy + jp*nwz + kp*nw + lp]*xWta) * yWta) * zWta) * wWta;         //        f[ip][jp][kp][lp]*xWta*yWta*zWta*wWta;
}

////////////////////////////////////////////////////////////////////////////////

double LI_5D(const int nx,
             const int ny,
             const int nz,
             const int nw,
             const int nv,
             const double *x,
             const double *y,
             const double *z,
             const double *w,
             const double *v,
             const double *f,
             const double xP,
             const double yP,
             const double zP,
             const double wP,
             const double vP){

    int i = get_location_dim(nx,x,xP);
    int j = get_location_dim(ny,y,yP);
    int k = get_location_dim(nz,z,zP);
    int l = get_location_dim(nw,w,wP);
    int m = get_location_dim(nv,v,vP);

    int ip = i+1;
    int jp = j+1;
    int kp = k+1;
    int lp = l+1;
    int mp = m+1;

    double xWta = (xP - x[i])/(x[i+1]-x[i]);
    double yWta = (yP - y[j])/(y[j+1]-y[j]);
    double zWta = (zP - z[k])/(z[k+1]-z[k]);
    double wWta = (wP - w[l])/(w[l+1]-w[l]);
    double vWta = (vP - v[m])/(v[m+1]-v[m]);

    double xWtb = 1-xWta;
    double yWtb = 1-yWta;
    double zWtb = 1-zWta;
    double wWtb = 1-wWta;
    double vWtb = 1-vWta;

    int nvwzy = nv*nw*nz*ny;
    int nvwz  = nv*nw*nz;
    int nvw   = nv*nw;

    return ((((f[i *nvwzy + j *nvwz + k *nvw + l *nv + m ]*xWtb +                                         // return f[i ][j ][k ][l ][m ]*xWtb*yWtb*zWtb*wWtb*vWtb +
               f[ip*nvwzy + j *nvwz + k *nvw + l *nv + m ]*xWta) * yWtb +                                 //        f[ip][j ][k ][l ][m ]*xWta*yWtb*zWtb*wWtb*vWtb +
              (f[i *nvwzy + jp*nvwz + k *nvw + l *nv + m ]*xWtb +                                         //        f[i ][jp][k ][l ][m ]*xWtb*yWta*zWtb*wWtb*vWtb +
               f[ip*nvwzy + jp*nvwz + k *nvw + l *nv + m ]*xWta) * yWta) * zWtb +                         //        f[ip][jp][k ][l ][m ]*xWta*yWta*zWtb*wWtb*vWtb +
             ((f[i *nvwzy + j *nvwz + kp*nvw + l *nv + m ]*xWtb +                                         //        f[i ][j ][kp][l ][m ]*xWtb*yWtb*zWta*wWtb*vWtb +
               f[ip*nvwzy + j *nvwz + kp*nvw + l *nv + m ]*xWta) * yWtb +                                 //        f[ip][j ][kp][l ][m ]*xWta*yWtb*zWta*wWtb*vWtb +    
              (f[i *nvwzy + jp*nvwz + kp*nvw + l *nv + m ]*xWtb +                                         //        f[i ][jp][kp][l ][m ]*xWtb*yWta*zWta*wWtb*vWtb +
               f[ip*nvwzy + jp*nvwz + kp*nvw + l *nv + m ]*xWta) * yWta) * zWta) * wWtb +                 //        f[ip][jp][kp][l ][m ]*xWta*yWta*zWta*wWtb*vWtb +
            (((f[i *nvwzy + j *nvwz + k *nvw + lp*nv + m ]*xWtb +                                         //        f[i ][j ][k ][lp][m ]*xWtb*yWtb*zWtb*wWta*vWtb +
               f[ip*nvwzy + j *nvwz + k *nvw + lp*nv + m ]*xWta) * yWtb +                                 //        f[ip][j ][k ][lp][m ]*xWta*yWtb*zWtb*wWta*vWtb +
              (f[i *nvwzy + jp*nvwz + k *nvw + lp*nv + m ]*xWtb +                                         //        f[i ][jp][k ][lp][m ]*xWtb*yWta*zWtb*wWta*vWtb +
               f[ip*nvwzy + jp*nvwz + k *nvw + lp*nv + m ]*xWta) * yWta) * zWtb +                         //        f[ip][jp][k ][lp][m ]*xWta*yWta*zWtb*wWta*vWtb +
             ((f[i *nvwzy + j *nvwz + kp*nvw + lp*nv + m ]*xWtb +                                         //        f[i ][j ][kp][lp][m ]*xWtb*yWtb*zWta*wWta*vWtb +
               f[ip*nvwzy + j *nvwz + kp*nvw + lp*nv + m ]*xWta) * yWtb +                                 //        f[ip][j ][kp][lp][m ]*xWta*yWtb*zWta*wWta*vWtb +    
              (f[i *nvwzy + jp*nvwz + kp*nvw + lp*nv + m ]*xWtb +                                         //        f[i ][jp][kp][lp][m ]*xWtb*yWta*zWta*wWta*vWtb +
               f[ip*nvwzy + jp*nvwz + kp*nvw + lp*nv + m ]*xWta) * yWta) * zWta) * wWta) * vWtb +         //        f[ip][jp][kp][lp][m ]*xWta*yWta*zWta*wWta*vWtb +
           ((((f[i *nvwzy + j *nvwz + k *nvw + l *nv + mp]*xWtb +                                         //        f[i ][j ][k ][l ][mp]*xWtb*yWtb*zWtb*wWtb*vWta +
               f[ip*nvwzy + j *nvwz + k *nvw + l *nv + mp]*xWta) * yWtb +                                 //        f[ip][j ][k ][l ][mp]*xWta*yWtb*zWtb*wWtb*vWta +
              (f[i *nvwzy + jp*nvwz + k *nvw + l *nv + mp]*xWtb +                                         //        f[i ][jp][k ][l ][mp]*xWtb*yWta*zWtb*wWtb*vWta +
               f[ip*nvwzy + jp*nvwz + k *nvw + l *nv + mp]*xWta) * yWta) * zWtb +                         //        f[ip][jp][k ][l ][mp]*xWta*yWta*zWtb*wWtb*vWta +
             ((f[i *nvwzy + j *nvwz + kp*nvw + l *nv + mp]*xWtb +                                         //        f[i ][j ][kp][l ][mp]*xWtb*yWtb*zWta*wWtb*vWta +
               f[ip*nvwzy + j *nvwz + kp*nvw + l *nv + mp]*xWta) * yWtb +                                 //        f[ip][j ][kp][l ][mp]*xWta*yWtb*zWta*wWtb*vWta +    
              (f[i *nvwzy + jp*nvwz + kp*nvw + l *nv + mp]*xWtb +                                         //        f[i ][jp][kp][l ][mp]*xWtb*yWta*zWta*wWtb*vWta +
               f[ip*nvwzy + jp*nvwz + kp*nvw + l *nv + mp]*xWta) * yWta) * zWta) * wWtb +                 //        f[ip][jp][kp][l ][mp]*xWta*yWta*zWta*wWtb*vWta +
            (((f[i *nvwzy + j *nvwz + k *nvw + lp*nv + mp]*xWtb +                                         //        f[i ][j ][k ][lp][mp]*xWtb*yWtb*zWtb*wWta*vWta +
               f[ip*nvwzy + j *nvwz + k *nvw + lp*nv + mp]*xWta) * yWtb +                                 //        f[ip][j ][k ][lp][mp]*xWta*yWtb*zWtb*wWta*vWta +
              (f[i *nvwzy + jp*nvwz + k *nvw + lp*nv + mp]*xWtb +                                         //        f[i ][jp][k ][lp][mp]*xWtb*yWta*zWtb*wWta*vWta +
               f[ip*nvwzy + jp*nvwz + k *nvw + lp*nv + mp]*xWta) * yWta) * zWtb +                         //        f[ip][jp][k ][lp][mp]*xWta*yWta*zWtb*wWta*vWta +
             ((f[i *nvwzy + j *nvwz + kp*nvw + lp*nv + mp]*xWtb +                                         //        f[i ][j ][kp][lp][mp]*xWtb*yWtb*zWta*wWta*vWta +
               f[ip*nvwzy + j *nvwz + kp*nvw + lp*nv + mp]*xWta) * yWtb +                                 //        f[ip][j ][kp][lp][mp]*xWta*yWtb*zWta*wWta*vWta +    
              (f[i *nvwzy + jp*nvwz + kp*nvw + lp*nv + mp]*xWtb +                                         //        f[i ][jp][kp][lp][mp]*xWtb*yWta*zWta*wWta*vWta +
               f[ip*nvwzy + jp*nvwz + kp*nvw + lp*nv + mp]*xWta) * yWta) * zWta) * wWta) * vWtb;          //        f[ip][jp][kp][lp][mp]*xWta*yWta*zWta*wWta*vWta;
}
