#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void main(){

FILE *userfile;
int c=0,i=0,j=0, unum;
char un[20],fiun[20],unu[1];
char pw[20], fpw[20];
printf("Welcome to the plot management system.\n");

while(1){  // Login 

printf("Enter Username: ");
gets(un);
printf("Enter password: ");
gets(pw);

unu[0]=un[4];
unum=atoi(unu); // atoi converts char/string to int

switch(unum){ // Opening userfile according to username using switchcase
case 1: userfile=fopen("User1.txt","r+");
break;
case 2: userfile=fopen("User2.txt","r+");
break;
case 3: userfile=fopen("User3.txt","r+");
break;
case 4: userfile=fopen("User4.txt","r+");
break;
case 5: userfile=fopen("User5.txt","r+");
break;
case 6: userfile=fopen("User6.txt","r+");
break;
case 7: userfile=fopen("User7.txt","r+");
break;
case 8: userfile=fopen("User8.txt","r+");
break;
case 9: userfile=fopen("User9.txt","r+");
break;
default: {printf("Incorrect Username!\n");
continue;}}

i=0;
c=0;

while(fgets(fiun,20,userfile)) //read each line in the file string by string
{
i++;
if(i==1){ // password is stored in second line of file so i=2
for(int j=0;j<strlen(fiun);j++){
if(un[j]==fiun[j]) // checking if entered password matches password in file
c++;
}
break;
}}

if(c!=strlen(un))
{printf("invalid username!\n");
continue;}

i=0;
c=0;

while(fgets(fpw,20,userfile)) //read each line in the file string by string
{
i++;
if(i==1){ // password is stored in second line of file so i=0 -> 1 in second loop
for(int j=0;j<strlen(fpw);j++){
if(pw[j]==fpw[j]) // checking if entered password matches password in file
c++;
}
break;
}}

if(c==strlen(pw))
{printf("Welcome %s\n",un);
break;}
else
printf("Incorrect Username or Pasword!\n");
} //Login Loop end

int buyplot=0;
char fp[20];

while(1){ // Buying and selling
printf("What would you like to do?\n");
printf("1.Buy Plots\n2.Sell Plots\n3.Add New Record\n4.Edit Record\n5.Delete Record\n6.Display Available Property\n7.Search\n");
printf("Enter your choice : ");
scanf("%d",&i);

if(i==1){  //Buy Loop
int j,p,q;

char plotgrid[4][5];
int row=0, col=0, plotno=1;  

printf("Here is the layout of plots.\n");
for(row=0;row<4;row++){
for(col=0;col<5;col++){
plotgrid[row][col]=plotno;
plotno++;
printf("%d\t",plotgrid[row][col]);
}
printf("\n");
}

FILE *plotfile1=fopen("PlotPrice.txt","r"); //This file has all available plots and their price 
FILE *plotfile2=fopen("AvialablePlots.txt","r"); // This file has the list of available plots to verify if user has entered a valid plot
char availableplot[1], plotprice[10];
int ap=0,c1=0,c2=0;

printf("Here's the list of available plots and their price: \n");
while(fgets(plotprice,2,plotfile1)) //Printing available plots from the file
printf("%s",plotprice);

printf("\nEnter the plot number you would like to buy: ");
scanf("%d",&buyplot);


c1=0;
c2=0;
while(fgets(availableplot,1,plotfile2)){ //checking is entered plot is in the file with available plots
c1++;
printf("%s",availableplot);
ap=atoi(availableplot);
if(ap==buyplot){
printf("You have chosen plot %d. Proceeding to payment.\n",buyplot);
break;
}
else 
c2++;
}

if(c1==c2){
c1=0;
c2=0;
//continue;
}

else 
break;
break;
}// Buy end

else if (i==2){ //Sell Loop
int plotlength, sprice, j=0;
char splot[1];
printf("Enter the price you would like to sell the plot for: ");
scanf("%d",&sprice);

while(fgets(fiun,20,userfile)){
j++;
if(j==2){
strcpy(splot, fiun); // copies fiun to splot
}}

printf("Plot number you are selling: %s\n", splot);
FILE *plotfile2=fopen("Availableplots.txt","a");
FILE *plotfile1=fopen("PlotPrice.txt","a");
fprintf(plotfile2, "\n%s", splot);
fprintf(plotfile1,"\n%s %d Rs.", splot, sprice);
break;

}// Sell end

else if(i == 3) { // Add New Record
    int plot_no, price;

    printf("Enter plot number: ");
    scanf("%d", &plot_no);

    printf("Enter plot price: ");
    scanf("%d", &price);

    FILE *available_plots = fopen("AvailablePlots.txt", "a");
    FILE *plot_price = fopen("PlotPrice.txt", "a");

    fprintf(available_plots, "\n%d", plot_no);
    fprintf(plot_price, "\n%d %d Rs.", plot_no, price);

    fclose(available_plots);
    fclose(plot_price);
}


else if (i == 4) { // Edit Record
    int plot_no=1, new_price, row_num = 0, col_num = 0;
    char grid[4][5], available_plot[20], price[20], temp[20], *token;

    // display the layout of plots
   printf("Here is the layout of plots.\n");
for (row_num = 0; row_num < 4; row_num++) {
    for (col_num = 0; col_num < 5; col_num++) {
        grid[row_num][col_num]=plot_no;
plot_no++;
printf("%d\t",grid[row_num][col_num]);
    }
    printf("\n");
}

    // get the plot to edit
    printf("Enter the plot number you want to edit: ");
    scanf("%d", &plot_no);

    // check if the plot is available
    FILE *available_plots_file = fopen("Availableplots.txt", "r");
    int available = 0;
    while (fgets(available_plot, 20, available_plots_file)) {
        token = strtok(available_plot, "\n");
        if (plot_no == atoi(token)) {
            available = 1;
            break;
        }
    }
    fclose(available_plots_file);

    if (!available) {
        printf("Plot not available!\n");
        continue;
    }

    // get the new price for the plot
    printf("Enter the new price for the plot: ");
    scanf("%d", &new_price);

    // update the plot price in the PlotPrice.txt file
    FILE *plot_prices_file = fopen("PlotPrice.txt", "r");
    FILE *temp_file = fopen("temp.txt", "w");
    while (fgets(price, 20, plot_prices_file)) {
        strcpy(temp, price);
        token = strtok(temp, " ");
        if (plot_no == atoi(token)) {
            fprintf(temp_file, "%d %d Rs.\n", plot_no, new_price);
        } else {
            fprintf(temp_file, "%s", price);
        }
    }
    fclose(plot_prices_file);
    fclose(temp_file);
    remove("PlotPrice.txt");
    rename("temp.txt", "PlotPrice.txt");

    printf("Record updated successfully!\n");
}



else if(i == 5) { // Delete Record
    int plot_no, count = 0;
    char line[100], temp[100];
    FILE *fp1, *fp2, *fp3, *fp4;

    printf("Enter the plot number to delete: ");
    scanf("%d", &plot_no);

    // Open original AvailablePlots file in read mode
    fp1 = fopen("AvailablePlots.txt", "r");

    // Create a temporary AvailablePlots file in write mode
    fp2 = fopen("temp1.txt", "w");

    // Open original PlotPrice file in read mode
    fp3 = fopen("PlotPrice.txt", "r");

    // Create a temporary PlotPrice file in write mode
    fp4 = fopen("temp2.txt", "w");

    // Read the contents of the original AvailablePlots file and copy all lines except the line to be deleted to the temporary AvailablePlots file
    while(fgets(line, 100, fp1)) {
        sscanf(line, "%d", &count);
        if(count != plot_no) {
            fprintf(fp2, "%s", line);
        }
    }

    // Read the contents of the original PlotPrice file and copy all lines except the line to be deleted to the temporary PlotPrice file
    while(fgets(line, 100, fp3)) {
        sscanf(line, "%d", &count);
        if(count != plot_no) {
            fprintf(fp4, "%s", line);
        }
    }

    // Close the files
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);

    // Remove the original AvailablePlots file
    remove("AvailablePlots.txt");

    // Remove the original PlotPrice file
    remove("PlotPrice.txt");

    // Rename the temporary AvailablePlots file as the original AvailablePlots file
    rename("temp1.txt", "AvailablePlots.txt");

    // Rename the temporary PlotPrice file as the original PlotPrice file
    rename("temp2.txt", "PlotPrice.txt");

    printf("Record with plot number %d has been deleted.\n", plot_no);
}



else if (i == 6) { // Display Available Property
    FILE *plotfile = fopen("AvailablePlots.txt", "r");
    int plotno = 0;
    printf("The following plots are available for purchase:\n");
    while (fscanf(plotfile, "%d", &plotno) != EOF) { // read plot numbers from file
        printf("%d\n", plotno);
    }
    fclose(plotfile);
    continue;
}




else if (i == 7) { // Search Loop
    int plot_no, flag = 0;
    char price[20];
    printf("Enter plot number to search: ");
    scanf("%d", &plot_no);

    // Search for the plot number in all user files
    for (int j = 1; j <= 9; j++) {
        char filename[20];
        sprintf(filename, "User%d.txt", j);
        FILE *userfile = fopen(filename, "r");

        if (userfile == NULL) {
            printf("Error: Unable to open file %s\n", filename);
            continue;
        }

        int i = 0;
        while (fgets(price, 20, userfile)) {
            i++;
            if (i == 2 && atoi(price) == plot_no) {
                flag = 1;
                printf("Plot %d is owned by User%d\n", plot_no, j);
                break;
            }
        }

        fclose(userfile);
    }

    if (!flag) {
        // Search for the plot number in the available plots file
        FILE *plotfile = fopen("AvailablePlots.txt", "r");
        int plotno = 0;
        while (fscanf(plotfile, "%d", &plotno) != EOF) {
            if (plotno == plot_no) {
                flag = 1;
                printf("Plot %d is available for purchase.\n", plot_no);
                break;
            }
        }
        fclose(plotfile);
    }

    if (!flag) {
        printf("Plot %d is not found.\n", plot_no);
    }
    continue;
}



else 
printf("Please enter a valid response.\n");

} // End of buying and selling


while(1) { // Payment Loop 

int p,q;

if(i==1){
printf("Enter pin: "); // pin is stored in 3rd line of file
scanf("%d",&q);
j=0;
while(fgets(fp,20,userfile)) // checking if pin is correct (similar to pw)
{
if(j==0){
p=atoi(fp);
}
j++;
}

if(p==q)
{printf("Payment Successful! Thank you for buying plot %d!",buyplot);
break;}

else 
{printf("Incorrect pin entered.\n");
continue;}
break;
}


else if (i==2){
printf("Thank you for putting your plot up for sale.\nYou will be notified if a buyer is interested.\n");
}
break;

} // End of Payment

}//4, 2, 3, 9, 7, 6, 11, 14, 10