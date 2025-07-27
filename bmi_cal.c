#include <stdio.h>
#include <math.h>
#include <string.h>

double calculate_bmi(double weight, double height) {
    return weight / pow((height / 100), 2);
}

void print_and_log_bmi(FILE *file, const char *name, double weight, double height, double bmi) {
    printf("\nYour name is %s\n", name);
    printf("Weight is %.2lf\n", weight);
    printf("Height is %.2lf\n", height);
    printf("BMI is %.2lf\n", bmi);

    fprintf(file, "Your name is %s\n", name);
    fprintf(file, "Weight is %.2lf\n", weight);
    fprintf(file, "Height is %.2lf\n", height);
    fprintf(file, "BMI is %.2lf\n", bmi);

    if(bmi < 18.5){
        printf("\nYou are underweight.\n");
        fprintf(file, "\nYou are underweight.\n");
    } 
    else if(bmi < 25.0){
        printf("\nYou have a normal weight.\n");
        fprintf(file, "\nYou have a normal weight.\n");
    } 
    else if(bmi < 30.0){
        printf("\nYou are overweight.\n");
        fprintf(file, "\nYou are overweight.\n");
    } 
    else{
        printf("\nYou are obese.\n");
        fprintf(file, "\nYou are obese.\n");
    }
    printf("----------------------------------------\n");
    fprintf(file, "----------------------------------------\n\n");
}

int input_double(const char *prompt, double *value){
    char buffer[50];
    printf("%s", prompt);
    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
        return 0;
    if (sscanf(buffer, "%lf", value) != 1)
        return 0;
    return 1;
}

int main(){
    char name[50];
    double weight, height, bmi;
    int rounds;

    FILE *file = fopen("output.txt", "w");
    if(file == NULL){
        printf("Error opening file!\n");
        return 1;
    }

    printf("Enter the number of rounds: ");
    if (scanf("%d", &rounds) != 1){
        printf("Invalid input for rounds.\n");
        fclose(file);
        return 1;
    }
    getchar(); // flush newline

    for(int i = 0; i<rounds; i++){
        printf("\nRound %d\n", i + 1);

        printf("Enter your name: ");
        if(fgets(name, sizeof(name), stdin) == NULL){
            printf("Error reading name.\n");
            fclose(file);
            return 1;
        }
        name[strcspn(name, "\n")] = '\0';

        if(!input_double("Enter your weight: ", &weight)){
            printf("Invalid weight input.\n");
            fclose(file);
            return 1;
        }
        if(!input_double("Enter your height: ", &height)){
            printf("Invalid height input.\n");
            fclose(file);
            return 1;
        }
        if(height == 0){
            printf("Height cannot be zero.\n");
            fclose(file);
            return 1;
        }

        bmi = calculate_bmi(weight, height);
        print_and_log_bmi(file, name, weight, height, bmi);
    }

    printf("\nResult written to output.txt\n");
    fclose(file);
    return 0;
}
