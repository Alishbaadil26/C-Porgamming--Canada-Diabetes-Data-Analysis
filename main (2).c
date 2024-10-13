#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max_num_elements 1000
#define max_string_length 1000

double average(double sum, double tot){
  //this simple function calculates the average when given the sum and total #
  double average;
  average=(sum/tot);
  return(average); //returns the average
}

int main() {
  
  char row[max_string_length];
  char ref_date[max_num_elements][max_string_length];
  char geo[max_num_elements][max_string_length];
  char value[max_num_elements][max_string_length];
  char age_group[max_num_elements][max_string_length];
  char sex[max_num_elements][max_string_length];

  int index = 0;
  // Reading file
  FILE *input_file = fopen("statscan_diabetes.csv", "r");
  if (input_file == NULL) {
    printf("error opening input file.");
    return 1;
  }

  while (fgets(row, max_string_length, input_file)) {
    char *element = strtok(row, ",\"");
    int counter = 0;
    while (element != NULL && counter < 15) {
      if (element[0] == '\0') {
        element = strtok(NULL, ",\"");
        counter++;
        continue; // skipping empty cells
      }

      if (counter == 0) {
        strcpy(ref_date[index], element);
      } else if (counter == 1) {
        strcpy(geo[index], element);
      } else if (counter == 2) {
        if (strcmp(geo[index], "Canada (excluding territories)") == 0) {
          strcpy(age_group[index], element);
        }
      } else if (counter == 3) {
        if (strcmp(geo[index], "Canada (excluding territories)") == 0) {
          strcpy(sex[index], element);
        } else {
          strcpy(age_group[index], element);
        }
      } else if (counter == 4) {
        if (strcmp(geo[index], "Canada (excluding territories)") != 0) {
          strcpy(sex[index], element);
        }
      } else if (counter == 12) {
        if (strcmp(geo[index], "Canada (excluding territories)") == 0) {
          strcpy(value[index], element);
        }
      } else if (counter == 13) {
        if (strcmp(geo[index], "Canada (excluding territories)") != 0) {
          strcpy(value[index], element);
        }
      }
      element = strtok(NULL, ",\"");
      counter++;
    }
    index++;
  }
 
  /*************************Part 1A**************************/
  //Determine the following averages of the percentage of the population that are diagnosed with diabetes.
  //PART A: Provincial averages (Ontario, Quebec, British Columbia, Alberta). One average per province (for all years and age groups).
  printf("\nQuestion 1 Part A\n");
  printf("==================\n");

  //Assigning variables for average calculations
  double Ontario_Sum;
  double Ontario_Total;

  double Quebec_Sum;
  double Quebec_Total;

  double BC_Sum;
  double BC_Total;

  double Alberta_Sum;
  double Alberta_Total;

  for (int i = 0; i <= index; i++) {
    switch (geo[i][0]) {
    case 'O':
      if (strcmp(geo[i], "Ontario") == 0 && atof(value[i]) != 0) {
        Ontario_Sum += atof(value[i]);
        Ontario_Total++;
      }
      break;
    case 'Q':
      if (strcmp(geo[i], "Quebec") == 0 && atof(value[i]) != 0) {
        Quebec_Sum += atof(value[i]);
        Quebec_Total++;
      }
      break;
    case 'B':
      if (strcmp(geo[i], "British Columbia") == 0 && atof(value[i]) != 0) {
        BC_Sum += atof(value[i]);
        BC_Total++;
      }
      break;
    case 'A':
      if (strcmp(geo[i], "Alberta") == 0 && atof(value[i]) != 0) {
        Alberta_Sum += atof(value[i]);
        Alberta_Total++;
      }
      break;
    }
  }

  double Ontario_Average = average(Ontario_Sum,Ontario_Total);
  double Quebec_Average = average(Quebec_Sum,Quebec_Total);
  double BC_Average = average(BC_Sum,BC_Total);
  double Alberta_Average = average(Alberta_Sum,Alberta_Total);
 
  printf("Provincial average diagnosed with diabetes in: \n");
  printf("==============================================\n");
  printf("1.Ontario\t\t\t\t = %0.2f%%\t\t\t |\n",Ontario_Average);
  printf("2.Alberta\t\t\t\t = %0.2f%%\t\t\t |\n",Alberta_Average);
  printf("3.British Columbia\t\t = %0.2f%%\t\t\t |\n",BC_Average);
  printf("4.Quebec\t\t\t\t = %0.2f%%\t\t\t |\n",Quebec_Average);
  printf("==============================================\n");

  
  /*************************Part 1B**************************/
  //PART B: One national (Canada excluding territories) average for all years and age groups.
  printf("\nQuestion 1 Part B\n");
  printf("==================\n");
  //assign variables
  double n_sum = 0; //to store the sum for the national average
  double n_total = 0; //to store the total for the national average

  for (int i = 0; i <= index; i++) {
    float val = atof(value[i]);
    switch (geo[i][0]) {
    case 'C':
      if (strcmp(geo[i], "Canada (excluding territories)") == 0 && val != 0) {
        n_sum += val;
        n_total++;
      }
      break;
    }
  }
  double national_average = average(n_sum, n_total); //funtion for average
  printf("==============================================\n");
  printf("The national average\t = %0.2f%%\t\t\t |\n", national_average);
  printf("==============================================\n");

  
  /*************************Part 1C**************************/
  printf("\nQuestion 1 Part C\n");
  printf("==================\n");
  printf("One average per year for each province:\n");
  printf("=====================================================================\n");
  printf("Year\t|\t ON\t\t|\t QU\t\t|\t BC\t\t|\t AL\t\t|\t CAN\t|\n");
  printf("=====================================================================\n");

  //Part C:Yearly averages (2015, 2016, 2017, 2018, 2019, 2020, 2021). One average per year (all age groups together) for each province and the whole country (Canada excluding territories) for a total of 35 averages.
  for (int year = 2015; year <= 2021; year++) {
    //runs through each year from 2015-2021
    double onsum = 0;
    double ontotal = 0;

    double quesum = 0;
    double quetotal = 0;

    double bcsum = 0;
    double bctotal = 0;

    double albsum = 0;
    double albtotal = 0;

    double cansum = 0;
    double cantotal = 0;
 for (int i = 0; i <= index; i++) {
      if (strcmp(ref_date[i], "Ref_Date") == 0) {
        continue;
      }
      if (atoi(ref_date[i]) == year && atof(value[i]) != 0) {
        switch (geo[i][0]) {
        case 'O':
          if (strcmp(geo[i], "Ontario") == 0) {
            onsum += atof(value[i]);
            ontotal++;
          }
          break;
        case 'Q':
          if (strcmp(geo[i], "Quebec") == 0) {
            quesum += atof(value[i]);
            quetotal++;
          }
          break;
        case 'B':
          if (strcmp(geo[i], "British Columbia") == 0) {
            bcsum += atof(value[i]);
            bctotal++;
          }
          break;
        case 'A':
          if (strcmp(geo[i], "Alberta") == 0) {
            albsum += atof(value[i]);
            albtotal++;
          }
          break;
        case 'C':
          if (strcmp(geo[i], "Canada (excluding territories)") == 0) {
            cansum += atof(value[i]);
            cantotal++;
          }
          break;
        }
      }
    }

    // averages
    double onavg = average(onsum, ontotal);
    double queavg = average(quesum, quetotal);
    double bcavg = average(bcsum, bctotal);
    double albavg = average(albsum, albtotal);
    double canavg = average(cansum, cantotal);
   printf("%d\t|%0.2f%%\t\t|\t%0.2f%%\t|\t%0.2f%%\t|\t%0.2f%%\t|\t%0.2f%%\t|\n",year,onavg,queavg,bcavg,albavg,canavg);//prints the information for each year
  
  
  }
  printf("=====================================================================\n");

  
  /*************************Part 1D**************************/
  //PART D:The average percentage of diabetes among age groups (35-49, 60-64, 65+). One average per age group (all years) for each province and the whole country (Canada excluding territories) .
  printf("\nQuestion 1 Part D\n");
  printf("==================\n");
  printf("Average percentage of diabetes for age groups (35-49, 60-64, 65+):\n");    
  printf("=================================================================================\n");
  printf("Ages\t\t\t\t|\tON\t\t|\t QU\t\t|\t BC\t\t|\t AL\t\t|\t CAN\t|\n");
  printf("=================================================================================\n");
  char* agegroups[]={"35 to 49 years", "50 to 64 years", "65 years and over"};

  for(int j =0; j<3; j++)
    {
      char* currentgroup = agegroups[j];
      double onsum=0, ontotal=0, quesum=0, quetotal=0, bcsum=0, bctotal=0, albsum=0, albtotal=0, cansum=0, cantotal=0;

      for(int i=0; i<=index; i++)
        {
          if(strcmp(age_group[i],currentgroup) ==0  &&atof(value[i])!=0)
          {
            switch(geo[i][0])
              {
                case 'O':
                  if(strcmp(geo[i],"Ontario")==0){
                  onsum+=atof(value[i]);
                  ontotal++;
                  }
                  break;
                case 'Q':
                if(strcmp(geo[i],"Quebec")==0){
                quesum+=atof(value[i]);
                quetotal++;
                }
                break;
                case 'B':
                if(strcmp(geo[i],"British Columbia")==0){
                bcsum+=atof(value[i]);
                bctotal++;
                }
                break;
                case 'A':
                if(strcmp(geo[i],"Alberta")==0){
                albsum+=atof(value[i]);
                albtotal++;
                }
                break;
                case 'C':
                if(strcmp(geo[i],"Canada (excluding territories)")==0){
                cansum+=atof(value[i]);
                cantotal++;
                }
                break;
          } 
        }
    }
  double onavg=average(onsum,ontotal);
  double queavg=average(quesum,quetotal);
  double bcavg=average(bcsum,bctotal);
  double albavg=average(albsum,albtotal);
  double canavg=average(cansum,cantotal);

//If statement for aesthetic purposes of the chart
if (strcmp(currentgroup, "65 years and over") == 0) {
    printf("%s\t|%0.2f%%\t\t|\t%0.2f%%\t|\t%0.2f%%\t|\t%0.2f%%\t|\t%0.2f%%\t|\n", currentgroup, onavg, queavg, bcavg, albavg, canavg);
} else {
    printf("%s\t\t|%0.2f%%\t\t|\t%0.2f%%\t|\t%0.2f%%\t|\t%0.2f%%\t|\t%0.2f%%\t|\n", currentgroup, onavg, queavg, bcavg, albavg, canavg);
}

      
}
   printf("=================================================================================\n"); 

  /*************************Part 2**************************/
  //PART 2:Determine which province has the highest percentage of diabetes (all years and age groups together as calculated in question 1a) and which province has the lowest percentage. 
  printf("\nQuestion 2\n");
  printf("===========\n");
  printf("Highest percentage of diabetes (all years and age groups together as calculated \nin question 1a):\n");    
  printf("=================================================================================\n");
  double listofaverages[] = {Ontario_Average, Alberta_Average, BC_Average,
                             Quebec_Average};

  double largest;
  largest = listofaverages[0];

  for (int i = 0; i < 4; i++) {
    if (listofaverages[i] > largest) {
      largest = listofaverages[i];
    }
  }

  double smallest;
  smallest = listofaverages[0];

  for (int i = 0; i < 4; i++) {
    if (listofaverages[i] < smallest) {
      smallest = listofaverages[i];
    }
  }

  char largestchar[100];
  if (largest == Ontario_Average) {
    strcpy(largestchar, "Ontario");
  } else if (largest == Alberta_Average) {
    strcpy(largestchar, "Alberta");
  }

  else if (largest == BC_Average) {
    strcpy(largestchar, "British Comlumbia");
  }

  else if (largest == Quebec_Average) {
    strcpy(largestchar, "Ontario");
  }

  char smallestchar[100];

  if (smallest == Ontario_Average) {
    strcpy(smallestchar, "Ontario");
  } else if (smallest == Alberta_Average) {
    strcpy(smallestchar, "Alberta");
  }

  else if (smallest == BC_Average) {
    strcpy(smallestchar, "British Comlumbia");
  }

  else if (smallest == Quebec_Average) {
    strcpy(smallestchar, "Ontario");
  }

  printf("The province with the highest percentage of diabetes of all age "
         "groups is:\t\t| \n%s with: %.2lf%%\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\nThe province with the smallest "
         "percentage of diabetes of all age groups is:\t\t|\n%s with: %.2lf%%\t\t\t\t\t\t\t\t\t\t\t\t\t|\n",
         largestchar, largest, smallestchar, smallest);
    printf("=================================================================================\n");

 
  /*************************Part 3**************************/
//PART 3:Indicate the provinces that have diabetes percentages above the national average (Canada excluding territories)  and the provinces that are below the national average. 
  printf("\nQuestion 3\n");
  printf("===========\n");
  printf("The provinces that have diabetes percentages above the national average (Canada \nexcluding territories) and the provinces that are below the national average:\n");    
  printf("=================================================================================\n");
  printf("National average diabetes percentage: %.2f%%\t\t\t\t\t\t\t\t\t|\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n", national_average);

  if (Ontario_Average > national_average) {
    printf(
        "The diabetes percentage of Ontario is above the national average.\t\t\t\t|\n");
  } else {
    printf(
        "The diabetes percentage of Ontario is below the national average.\t\t\t\t|\n");
  }

  if (Quebec_Average > national_average) {
    printf(
        "The diabetes percentage of Quebec is above the national average.\t\t\t\t|\n");
  } else {
    printf(
        "The diabetes percentage of Quebec is below the national average.\t\t\t\t|\n");
  }

  if (BC_Average > national_average) {
    printf("The diabetes percentage of British Columbia is above the national "
           "average.\t\t|\n");
  } else {
    printf("The diabetes percentage of British Columbia is below the national "
           "average.\t\t|\n");
  }

  if (Alberta_Average > national_average) {
    printf(
        "The diabetes percentage of Alberta  is above the national average.\t\t\t\t|\n");
  } else {
    printf(
        "The diabetes percentage of Alberta  is below the national average.\t\t\t\t|\n");
  }
  printf("=================================================================================\n");

  /*************************Part 4**************************/
  //PART 4:Indicate which year and province has the highest percentage of diabetes. Do the same for the lowest percentage. In case of a tie, you can mention multiple years and provinces.
  printf("\nQuestion 4\n");
  printf("===========\n");
  printf("The highest and lowest percentage of diabetes  with its year and province:\n");    
  printf("=================================================================================\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
int highest_year = 2015; // initialize the year with the highest value
double highest_value = 0; // initialize the maximum value
char* highest_province = ""; // initialize the province with the highest value
for(int year=2015; year<=2021;year++){
  double larg=0;
  char* larg_province = ""; // initialize the province with the highest value for the current year
  for(int i=0;i<=index;i++){
    if(strcmp(ref_date[i],"Ref_Date")==0){
      continue;
    }
    if(atoi(ref_date[i])==year&&atof(value[i])!=0){
      switch(geo[i][0]){
        case 'O':
          if(strcmp(geo[i],"Ontario")==0){
            if (atof(value[i])>larg) {
              larg= atof(value[i]);
              larg_province = "Ontario";
            }
          }
          break;
        case 'Q':
          if(strcmp(geo[i],"Quebec")==0){
            if (atof(value[i])>larg) {
              larg= atof(value[i]);
              larg_province = "Quebec";
            }
          }
          break;
        case 'B':
          if(strcmp(geo[i],"British Columbia")==0){
              if (atof(value[i])>larg) {
                larg= atof(value[i]);
                larg_province = "British Columbia";
              }
          }
            break;
        case 'A':
          if(strcmp(geo[i],"Alberta")==0){
              if (atof(value[i])>larg) {
                larg= atof(value[i]);
                larg_province = "Alberta";
              }
          }
            break;
        case 'C':
          if(strcmp(geo[i],"Canada (excluding territories)")==0){
              if (atof(value[i])>larg) {
                larg= atof(value[i]);
                larg_province = "Canada (excluding territories)";
              }
          }
            break;
       }
     }
  }
  // check if the current year's maximum value is greater than the previous maximum value
  if (larg > highest_value) {
    highest_value = larg;
    highest_year = year;
    highest_province = larg_province;
  }
} 
// print the highest value, province and the year it occurred
printf("The year with the highest value is %d with a value of %0.2f%% in the province\t| \nof %s.\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|", highest_year, highest_value, highest_province);


/*For the smallest Question 4*/
int smallest_year = 2015; // initialize the year with the smallest value
double smallest_value = highest_value;  // initialize the smallest value
char* smallest_province = ""; // initialize the province with the smallest value
  
for(int year=2015; year<=2021;year++){
  double small=smallest_value;
  char* small_province = ""; // initialize the province with the smallest value for the current year
  
  for(int i=0;i<=index;i++){
    if(strcmp(ref_date[i],"Ref_Date")==0){
      continue;
    }
    if(atoi(ref_date[i])==year&&atof(value[i])!=0){
      switch(geo[i][0]){
        case 'O':
          if(strcmp(geo[i],"Ontario")==0){
            if (atof(value[i])<small) {
              small= atof(value[i]);
              small_province = "Ontario";
            }
          }
          break;
        case 'Q':
          if(strcmp(geo[i],"Quebec")==0){
            if (atof(value[i])<small) {
              small= atof(value[i]);
              small_province = "Quebec";
            }
          }
          break;
        case 'B':
          if(strcmp(geo[i],"British Columbia")==0){
              if (atof(value[i])<small) {
                small= atof(value[i]);
                small_province = "British Columbia";
              }
          }
            break;
        case 'A':
          if(strcmp(geo[i],"Alberta")==0){
              if (atof(value[i])<small) {
                small= atof(value[i]);
                small_province = "Alberta";
              }
          }
            break;
        case 'C':
          if(strcmp(geo[i],"Canada (excluding territories)")==0){
              if (atof(value[i])<small) {
                small= atof(value[i]);
                small_province = "Canada (excluding territories)";
              }
          }
            break;
       }
     }
  }
  // check if the current year's minimum value is greater than the previous minimum value
  if (small < smallest_value) {
    smallest_value = small;
    smallest_year = year;
    smallest_province = small_province;
  }
} 
// print the lowest value, province and the year it occurred
printf("\nThe year with the smallest value is %d with a value of %0.2f%% in the province\t|\nof %s\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n", smallest_year, smallest_value, smallest_province);
    printf("=================================================================================\n");
  return 0;
}
