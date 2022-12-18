#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <math.h>

void tab(int value){
    for(int i = 0; i < value; i++){
        printf(" ");
    }
}
  
int main()
{
    tab(27);
    printf("DRAG\n");  
    tab(20);
    printf("CREATIVE COMPUTING\n");
    tab(19);
    printf("MORRISTOWN NEW JERSEY\n");
    
    float P[2], E[2], W[2], S[2], X[2], M[2], C[2], B[2], Y[2], Q[2], D[2];


    printf("\n\n\n");
    printf("WELCOME TO DRAG STRIP.\n");
    printf("WOULD YOU LIKE THE INSTRUCTIONS? ");

    char i;
    scanf("%s", &i);
    if (strcmp (&i, "NO")  == 0){
        goto n110;
    } else {
        goto YES;
    }
    YES:
        printf("YOU MAY RACE AGAINST ONE OF YOUR FRIENDS OR YOU MAY RACE\n");
        printf("AGAINST MY DRAGSTER. YOU WILL BE ASKED TO DESIGN YOUR\n");
        printf("OWN MACHINE, SPECIFYING HOURSEPOWER, READ END RATIO (X:1),\n");
        printf("TIRE WIDTH IN INCHES AND TIRE DIAMETER IN FEET.\n");

    n110:
        printf("DO YOU WANT TO RACE AGAINST ME? ");
        scanf("%s",&i);
        if (strcmp (&i, "NO")  == 0){
            goto n200;
        } else {
            printf("I WILL HAVE CAR #1.\n");
            P[0] = 600;
            E[0] = 5.9;
            W[0] = 22;
            D[0] = 3.9;
            goto n290;
        }
    n200:
        printf("DESIGN CAR #1: ");
        printf("HOURSPOWER = ");
        scanf("%f", &P[0]);
        printf("REAR END RATIO = ");
        scanf("%f", &E[0]);
        printf("TIRE WIDTH = ");
        scanf("%f", &W[0]);
        printf("TIRE DIAMETER = ");
        scanf("%f", &D[0]);

    n290:
        printf("DESIGN CAR #2:");
        printf("HORSEPOWER = ");
        scanf("%f", &P[1]);
        printf("REAR END RATIO = ");
        scanf("%f", &E[1]);
        printf("TIRE WIDTH = ");
        scanf("%f", &W[1]);
        printf("TIRE DIAMETER = ");
        scanf("%f", &D[1]);
        printf("\n");
        printf("GO!\n");
    int K1 = 500;
    float K2 = 1.6;
    int K3 = 2;
    float K4 = 0.0006;
    float K5 = 0.00006;
    float K6 = 0.2;
    int K7 = 4;
    float K8 = 0.00015;
    Q[0] = 0;
    Q[1] = 0;
    S[0] = 0;
    S[1] = 0;
    X[0] = 0;
    X[1] = 0;
    
    int j;
    for (j = 0; j<2; j++){
        M[j] = (K1 + K2 * P[j] + K3 * W[j] * D[j] + K7 * pow(D[j],2)) / 32.2; //M IS MASS
        C[j] = K4 * pow(M[j],(2/3)) + K8 * W[j]*D[j]; //C IS DRAG FROM WIND.
        B[j] = 15 + 28 * W[j] * D[j] / ((W[j] + 6) * (D[j] + 1)); // B IS THE MAX ACCELERATION WITHOUT BURNING
        Y[j] = 3.7 - 0.0033 * P[j]; //Y IS THE SCALE FACTOR FOR RPN VS POUER.
        }
    printf("\n\n");
    printf("ELAPSED ");
    tab(4);
    printf("CAR #1");
    tab(17);
    printf("CAR #2\n");
    printf("TIME   SPEED     DISTANCE     SPEED     DISTANCE\n");
    printf("(SEC)  (MPH)      (FT)        (MPH)        (FT)\n\n");
    float T;
    float T1;
    float A;
    float T3;
    for (T = 0; T < 101; T++){
        for(T1 = 1; T1 < 101; T1++){
            for (j = 0; j < 2; j++){ 
                float R,L0,L1,L2,F;
                R = 60 * S[j] * E[j] / (3.1415926 * D[j]); //R IS RPM.
                L0 = (P[j] / 42.5) * (50 + 0.0078 * (R / Y[j]) - 0.0000000004 * pow((R / Y[j]),3)); //L0 IS ENGINE TORQUE.
                L1 = P[j] * (K5 * R + K6); //L1 IS TORQUE FROM FRICTION.
                L2 = E [j] * (L0 - L1); //L2 IS REAR AXLE TORQUE.
                F = 2 * L2 / D[j]; //F IS FORCE ON ROAD FROM TIRES.
                if (F > M[j] + B[j]){ //TEST FOR BURN.
                    A = B[j] - C[j] * pow(S[j],2) / M[j]; //A=ACCELERATION
                    goto n900; 
                } else {
                    if (Q[j] != 0){
                        A = (F - C[j] * pow(S[j],2)) / M[j]; //A=ACCELERATION
                        goto n900;
                    } else {
                        printf(" CAR #");
                        printf("%d", j+1);
                        printf(" STOPS BURNING RUBBER\n");
                        Q[j] = 1;
                        A = (F - C[j] * pow(S[j],2)) / M[j];
                        goto n900;
                    }
                }
                n900:
                    S[j] = S[j] + A * 0.01; //S IS FEET IN FT/SEC.
                    X[j] = X[j] + S[j] * 0.01; //X IS DISTANCE IN FT.  
            }
            if ((X[0] >= 5280 / 4) || (X[1] >= 5280 / 4)){ //TEST FOR FINISH.
                if (X[0] > X[1]){
                    T3 = (X[0] - 5280 / 4) / S[0];
                    T = T + T1/100 - T3;
                    X[0] = 5280 / 4;
                    X[1] = X[1] - S[1] * T3;
                    printf("%f", T);
                    printf("   ");
                    printf("%f", (S[0] * 3600 / 5280));
                    printf("   ");
                    printf("%f", X[0]);
                    printf("   ");
                    printf("%f", (S[1] * 3600 / 5280));
                    printf("   ");
                    printf("%f", X[1]);
                    printf("\n");
                    tab(10);
                    printf("WINNER\n");
                    goto n1040;
                    } else {
                        T3 = (X[1] - 5280/4) / S[1];
                        T = T + T1 / 100 - T3;
                        X[1] = 5280 / 4;
                        X[0] = X[0] - S[0] * T3;
                        printf("%f", T);
                        printf("    ");
                        printf("%f", S[0] * 3600 / 5280);
                        printf("   ");
                        printf("%f", X[0]);
                        printf("   ");
                        printf("%f", S[1] * 3600 / 5280);
                        printf("   ");
                        printf("%f", X[1]);
                        printf("\n");
                        tab(40);
                        printf("WINNER\n");
                        goto n1040;
                        }
                    n1040:
                        printf("DO YOU WANT TO TRY AGAIN? ");
                        char i;
                        scanf("%s", &i);
                        if (strcmp (&i, "YES")  == 0){
                            goto n110;
                            break;
                        } else {
                            goto n404;
                            break;
                        }
            }
        }
        printf("%f",(T + 1));
        printf("   ");
        printf("%f",(S[0] * 3600 / 5280));
        printf("   ");
        printf("%f",X[0]);
        printf("   ");
        printf("%f", (S[1] * 3600 / 5280));
        printf("   ");
        printf("%f", X[1]);
        printf("\n");
    }
    n404:
    printf("END.");
}
