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
printf("1.Buy Plots\n2.Sell Plots\n3.Add New Record\n4.Edit Record\n");
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


// else if(i == 4) { // Edit Record
// int plot_no, price;
// char line[20], *token;
// printf("Enter the plot number you want to edit: ");
// scanf("%d", &plot_no);

// // Open a temporary file to write the updated records to
// FILE *tempfile = fopen("temp.txt", "w");

// // Go through each line in the user's file and update the record with the matching plot number
// while(fgets(line, 20, userfile)) {
//     token = strtok(line, "\n"); // Remove the newline character from the line

//     if(atoi(token) == plot_no) { // Check if this is the line we want to edit
//         printf("Enter the new price for plot %d: ", plot_no);
//         scanf("%d", &price);

//         fprintf(tempfile, "%d\n%d\n", plot_no, price); // Write the updated record to the temporary file
//     } else {
//         fprintf(tempfile, "%s\n", line); // Write the existing record to the temporary file
//     }
// }

// // Close the user's file and the temporary file
// fclose(userfile);
// fclose(tempfile);

// // Replace the user's file with the temporary file
// remove("AvailablePlots.txt");
// rename("temp.txt", "AvailablePlots.txt");

// printf("Record updated successfully!\n");
// }

else { // Invalid choice
printf("Invalid choice! Please enter a number between 1 and 4.\n");
}
}

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