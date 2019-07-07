#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include<map>
using namespace std;

int mi[1000000][4];

int main()
{
	  char ver[2]; int row, col,x,_max,i,j,is_ascii;
	  FILE *f;
    printf("\nEnter the file name with extension:");
    char name[20];
    scanf("%s",name);
    f=fopen(name,"rb");
    fscanf(f,"%s",ver);
    ver[2]='\0';
    printf("%s",ver);
    fscanf(f,"%d",&col);
    fscanf(f,"%d",&row);

    if (strcmp(ver, "P1") == 0) {
        is_ascii = 1;
    }
    else if (strcmp(ver, "P4") == 0) {
        is_ascii = 0;
    }
    else {
        fprintf(stderr, "Error: Input file not in PBM format!\n");
        exit(1);
    }

    cout<<row<<" "<<col<<" ";

    cout << endl << "PROCESSING..........\n";

    int *img_in=(int *)malloc(sizeof(int)*row*col);
    printf("\n1265");

    int c;
    int lum_val;
    int k;i=0;

    /* Read the rest of the PBM file. */
    while ((c = fgetc(f)) != EOF) {
      ungetc(c, f);
      if (is_ascii == 1) {
        fscanf(f, "%d ", &lum_val);
        img_in[i++] = lum_val;
      } 
     else {
        lum_val = fgetc(f);
        /* Decode the image contents byte-by-byte. */
        for (k = 0; k < 8; k++) {
          img_in[i++] = (lum_val >> (7-k)) & 0x1;
        }
      }
    }

    int ctrs=i,ctrx=0;
    int **a=(int **)malloc(sizeof(int*)*row);
    for(i=0;i<row;i++)
      a[i]=(int *)malloc(sizeof(int)*col);

    int **z=(int **)malloc(sizeof(int*)*row);
    for(i=0;i<row;i++)
      z[i]=(int *)malloc(sizeof(int)*col);




    is_ascii=1;
    f=fopen("new_image.pbm","wb");
    fprintf(f,"%c%c\n%d %d\n",'P','1',col,row);

    int v,temp;

    for (i = 0; i < row; i++) {
      for (j = 0; j < col; j++) {
      if (is_ascii == 1) {
        fprintf(f, "%d ", img_in[i*col+j]);
      }
      else {
        temp = 0;
        for (k = 0; k < 8; k++) {
          v = img_in[i*col+j+k];
          temp |= (v << (7-k));
        }
        fprintf(f, "%c", temp);
      }

      if (((i*col+j) % (col+1)) == (col)) {
        fprintf(f, "\n");
      }
    }
  }
  fclose(f);


  int  ctrmax=i;
  ctrs=0;
  for(i=0;i<row;i++)
    for(j=0;j<col;j++)
        z[i][j]=a[i][j]=img_in[ctrs++];


 //Thinning  

//For Horizontal line
  int flag1=0;
  while(1){
    flag1=0;
    for(int i=0;i<row;i++){
      for(int j=0;j<col;j++){
        if(i+2<row && j+2<col)
        {
          if(a[i+1][j+1]==1 && a[i][j]==1 && a[i][j+1]==1 && a[i][j+2]==1 && a[i+2][j]==0 && a[i+2][j+1]==0 && a[i+2][j+2]==0)
          {
            flag1=1;
            a[i+1][j+1]=0;
            z[i+1][j+1]=0;
          }
        }
      }
    }
    if(flag1==0)
      break;
  }


  int flag2=0;
  while(1){
    flag2=0;
    for(int i=0;i<row;i++){
      for(int j=0;j<col;j++){
        if(i+2<row && j+2<col)
        {
          if(a[i+1][j+1]==1 && a[i][j]==1 && a[i][j+1]==1 && a[i+1][j]==0 &&a[i+1][j+2]==0 && a[i+2][j]==0 && a[i+2][j+1]==0 && a[i+2][j+2]==0)
          {
            flag2=1;
            a[i+1][j+1]=0;
            z[i+1][j+1]=0;
          }
        }
      }
    }
    if(flag2==0)
      break;
  }

  int flag3=0;
  while(1){
    flag3=0;
    for(int i=0;i<row;i++){
      for(int j=0;j<col;j++){
        if(i+2<row && j+2<col)
        {
          if(a[i+1][j+1]==1 && a[i][j+2]==1 && a[i][j+1]==1 && a[i+1][j]==0 &&a[i+1][j+2]==0 && a[i+2][j]==0 && a[i+2][j+1]==0 && a[i+2][j+2]==0)
          {
            flag3=1;
            a[i+1][j+1]=0;
            z[i+1][j+1]=0;
          }
        }
      }
    }
    if(flag3==0)
      break;
  }

  int flag4=0;
  while(1){
    flag4=0;
    for(int i=0;i<row;i++){
      for(int j=0;j<col;j++){
        if(i+3<row && j+3<col)
        {
          if(a[i+1][j+1]==1 && a[i+1][j+2]==1 && a[i][j]==1 && a[i][j+1]==1 && a[i][j+2]==1 && a[i][j+3]==1 && a[i+1][j]==0 &&a[i+1][j+3]==0 && a[i+2][j]==0 && a[i+2][j+1]==0 && a[i+2][j+2]==0 && a[i+2][j+3]==0)
          {
            flag4=1;
            a[i+1][j+1]=0;
            a[i+1][j+2]=0;
            z[i+1][j+1]=0;
            z[i+1][j+2]=0;
          }
        }
      }
    }
    if(flag4==0)
      break;
  }



  //For vertical line
  while(1){
    flag1=0;
    for(int i=0;i<row;i++){
      for(int j=0;j<col;j++){
        if(i+2<row && j+2<col)
        {
          if(a[i+1][j+1]==1 && a[i][j]==0 && a[i][j+2]==1 && a[i+1][j]==0 && a[i+1][j+2]==1 && a[i+2][j]==0 && a[i+2][j+2]==1)
          {
            flag1=1;
            a[i+1][j+1]=0;
            //a[i+2][j+2]=0;
            z[i+1][j+1]=0;
          }
        }
      }
    }
    if(flag1==0)
      break;
  }


  while(1){
    flag2=0;
    for(int i=0;i<row;i++){
      for(int j=0;j<col;j++){
        if(i+2<row && j+2<col)
        {
          if(a[i+1][j+1]==1 && a[i][j]==0 && a[i][j+1]==0 && a[i][j+2]==1 && a[i+1][j]==0 &&a[i+1][j+2]==1 && a[i+2][j]==0 && a[i+2][j+1]==0)
          {
            flag2=1;
            a[i+1][j+1]=0;
            z[i+1][j+1]=0;
          }
        }
      }
    }
    if(flag2==0)
      break;
  }

  while(1){
    flag3=0;
    for(int i=0;i<row;i++){
      for(int j=0;j<col;j++){
        if(i+2<row && j+2<col)
        {
          if(a[i+1][j+1]==1 && a[i][j]==0 && a[i][j+1]==0 && a[i+1][j]==0 && a[i+1][j+2]==1 && a[i+2][j]==0 && a[i+2][j+1]==0 && a[i+2][j+2]==1)
          {
            flag3=1;
            a[i+1][j+1]=0;
            z[i+1][j+1]=0;
          } 
        }
      }
    }
    if(flag3==0)
      break;
  }


  while(1){
    flag4=0;
    for(int i=0;i<row;i++){
      for(int j=0;j<col;j++){
        if(i+3<row && j+3<col)
        {
          if(a[i+1][j+1]==0 && a[i+1][j+2]==1 && a[i][j+1]==0 && a[i][j+2]==0 && a[i][j+3]==1 &&  a[i+1][j+3]==1 && a[i+2][j+1]==0 && a[i+2][j+2]==1 && a[i+2][j+3]==1 && a[i+3][j+1]==0 && a[i+3][j+2]==0 && a[i+3][j+3]==1)
          {
            flag4=1;
            a[i+1][j+2]=0;
            a[i+2][j+2]=0;
            z[i+1][j+2]=0;
            z[i+2][j+2]=0;
          }
        }
      }
    }
    if(flag4==0)
      break;
  }

  //for Diagonal line
  while(1){
    flag1=0;
    for(int i=0;i<row;i++){
      for(int j=0;j<col;j++){
        if(i+2<row && j+2<col)
        {
          if(a[i+1][j+1]==1 && a[i][j+1]==1 && a[i+1][j]==1 && a[i+1][j+2]==0 && a[i+2][j+1]==0 && a[i+2][j+2]==0)
          {
            flag1=1;
            a[i+1][j+1]=0;
            z[i+1][j+1]=0;
          } 
        }
      }
    }
    if(flag1==0)
      break;
  }



  while(1){
    flag2=0;
    for(int i=0;i<row;i++){
      for(int j=0;j<col;j++){
        if(i+2<row && j+2<col)
        {
          if(a[i+1][j+1]==1 && a[i][j]==0 && a[i][j+1]==0 && a[i+1][j]==0 && a[i+1][j+2]==1 && a[i+2][j+1]==1)
          { 
            flag2=1;
            a[i+1][j+1]=0;
            z[i+1][j+1]=0;
          }
        }
      }
    }
    if(flag2==0)
      break;
  }


  while(1){
    flag3=0;
    for(int i=0;i<row;i++){
      for(int j=0;j<col;j++){
        if(i+2<row && j+2<col)
        {
          if(a[i+1][j+1]==1 && a[i][j+1]==1 && a[i+1][j]==0 && a[i+1][j+2]==1 && a[i+2][j]==0 && a[i+2][j+1]==0){
            flag3=1;
            a[i+1][j+1]=0;
            z[i+1][j+1]=0;
          }
        }
      }
    }
    if(flag3==0)
      break;
  }


  while(1){
    flag4=0;
    for(int i=0;i<row;i++){
      for(int j=0;j<col;j++){
        if(i+2<row && j+2<col)
        {
          if(a[i+1][j+1]==1 && a[i][j+1]==0 && a[i][j+2]==0 && a[i+1][j]==1 && a[i+1][j+2]==0 && a[i+2][j+1]==1){
            flag4=1;
            a[i+1][j+1]=0;
            z[i+1][j+1]=0;
          }
        }
      }
    }
    if(flag4==0)
      break;
  }


  //noise elimination
  while(1){
    flag1=0;
    for(int i=0;i<row;i++){
      for(int j=0;j<col;j++){
        if(i+2<row && j+2<col)
        {
          if(a[i+1][j+1]==1 && a[i][j+1]==0 && a[i][j+2]==0 && a[i+1][j]==1 && a[i+1][j+2]==0 &&  a[i+2][j]==1 && a[i+2][j+1]==0 && a[i+2][j+2]==0)
          {
            flag1=1;
            a[i+1][j+1]=0;
            z[i+1][j+1]=0;
          }
        }
      }
    }
    if(flag1==0)
      break;
  }



  while(1){
    flag2=0;
    for(int i=0;i<row;i++){
      for(int j=0;j<col;j++){
        if(i+2<row && j+2<col)
        {
          if(a[i+1][j+1]==1 && a[i][j]==0 && a[i][j+1]==0 && a[i][j+2]==1 && a[i+1][j]==0 && a[i+1][j+2]==0 && a[i+2][j]==1 && a[i+2][j+1]==1)
          { 
            flag2=1;
            a[i+1][j+1]=0;
            z[i+1][j+1]=0;
          }
        }
      } 
    }
    if(flag2==0)
      break;
  }


  while(1){
    flag3=0;
    for(int i=0;i<row;i++){
      for(int j=0;j<col;j++){
        if(i+2<row && j+2<col)
        {
          if(a[i+1][j+1]==1 && a[i][j]==0 && a[i][j+1]==0 && a[i][j+2]==0 && a[i+1][j]==0 && a[i+1][j+2]==0 && a[i+2][j]==0 && a[i+2][j+1]==0 && a[i+2][j+2]==0){
            flag3=1;
            a[i+1][j+1]=0;
            z[i+1][j+1]=0;
          }
        }
      }
    }
    if(flag3==0)
      break;
  }

  char name1[20]="Thinned_";
  
  for(i = 0; name1[i] != '\0'; ++i);

  for(j = 0; name[j] != '\0'; ++j, ++i)
  {
    name1[i] = name[j];
  }

  f=fopen(name1,"wb");
  fprintf(f,"%c%c\n%d %d\n",'P','1',col,row);


   for (i = 0; i < row; i++) {
    for (j = 0; j < col; j++) {
    if (is_ascii == 1) {
        fprintf(f, "%d ", a[i][j]);
    }
    else {
      temp = 0;
      for (k = 0; k < 8; k++) {
          v = img_in[i*col+j+k];
          temp |= (v << (7-k));
      }
        fprintf(f, "%c", temp);
    }

    if (((i*col+j) % (col+1)) == (col)) {
        fprintf(f, "\n");
      }
    }
  }

  fclose(f);
  /*for(i=0;i<row;i++)
  {
	 for(j=0;j<col;j++)
    	cout<<z[i][j]<<"  ";
    	cout<<"\n";
  }*/

  /*f=fopen("Thinned2.pbm","wb");
  fprintf(f,"%c%c\n%d %d\n",'P','1',col,row);


   for (i = 0; i < row; i++) {
    for (j = 0; j < col; j++) {
    if (is_ascii == 1) {
        fprintf(f, "%d ", z[i][j]);
    }
    else {
      temp = 0;
      for (k = 0; k < 8; k++) {
          v = img_in[i*col+j+k];
          temp |= (v << (7-k));
      }
        fprintf(f, "%c", temp);
    }

    if (((i*col+j) % (col+1)) == (col)) {
        fprintf(f, "\n");
      }
    }
  }

  fclose(f);*/

  printf("\nThinning Completed\n");
  //minutiae extraction
  int count1=0,count2=0;

  int t=0;
    for(i=0;i<row;i++)
    {
      for(j=0;j<col;j++)
      {
        if(i+2<row && j+2<col)
        {
          t=0;
          if(a[i+1][j+1]==1)
          {
          /*continue;
          }
          else{*/
          /*cout<<i<<" "<<j<<" "<<"\t";*/
            t=a[i][j]+a[i][j+1]+a[i][j+2]+a[i+1][j]+a[i+1][j+2]+a[i+2][j]+a[i+2][j+1]+a[i+2][j+2];
            if(t==1)
            {
              mi[count1+count2][0]=i+1; 
              mi[count1+count2][1]=j+1;
              mi[count1+count2][2]=1;
              count1++;
              if((i+5<row && j+5<col) &&(i-5>=0 && j-5>=0) )
              {
                z[i-1][j-1]=1;
                z[i][j-1]=1;
                z[i+1][j-1]=1;
                z[i+2][j-1]=1;
                z[i+3][j-1]=1;

                z[i-1][j+3]=1;
                z[i][j+3]=1;
                z[i+1][j+3]=1;
                z[i+2][j+3]=1;
                z[i+3][j+3]=1;   

                z[i-1][j-1]=1;
                z[i-1][j]=1;
                z[i-1][j+1]=1;
                z[i-1][j+2]=1;
                z[i-1][j+3]=1;

                z[i+3][j-1]=1;
                z[i+3][j]=1;
                z[i+3][j+1]=1;
                z[i+3][j+2]=1;
                z[i+3][j+3]=1;                             
              }
            }

            if(t==3)
            {
              if (!((a[i][j]==1 && a[i+1][j]==1 && a[i+2][j]==1) || (a[i][j]==1 && a[i][j+1]==1 && a[i][j+2]==1) || (a[i][j+2]==1 && a[i+1][j+2]==1 && a[i+2][j+2]==1) || (a[i+2][j]==1 && a[i+2][j+1]==1 && a[i+2][j+2]==1)))
              {
                /*continue;
                }*/
                mi[count1+count2][0]=i+1;
                mi[count1+count2][1]=j+1;
                mi[count1+count2][2]=2;
                count2++;
                if((i+5<row && j+5<col) &&(i-5>=0 && j-5>=0) )
                {
                  z[i-1][j-1]=1;
                  z[i][j-1]=1;
                  z[i+1][j-1]=1;
                  z[i+2][j-1]=1;
                  z[i+3][j-1]=1;

                  z[i-1][j+3]=1;
                  z[i][j+3]=1;
                  z[i+1][j+3]=1;
                  z[i+2][j+3]=1;
                  z[i+3][j+3]=1;   

                  z[i-1][j-1]=1;
                  z[i-1][j]=1;
                  z[i-1][j+1]=1;
                  z[i-1][j+2]=1;
                  z[i-1][j+3]=1;

                  z[i+3][j-1]=1;
                  z[i+3][j]=1;
                  z[i+3][j+1]=1;
                  z[i+3][j+2]=1;
                  z[i+3][j+3]=1;                             
                }
              }
            }
          }
        }
      }
    }
    cout<<endl<<"MINUTIAE"<<count1<<" "<<count2;

  char name2[20]="Marked_Thinned_";
  
  for(i = 0; name2[i] != '\0'; ++i);

  for(j = 0; name[j] != '\0'; ++j, ++i)
  {
    name2[i] = name[j];
  }

    
  f=fopen(name2,"wb");
  fprintf(f,"%c%c\n%d %d\n",'P','1',col,row);


  for (i = 0; i < row; i++) {
    for (j = 0; j < col; j++) {
      if (is_ascii == 1) {
        fprintf(f, "%d ", z[i][j]);
      }
      else {
        temp = 0;
        for (k = 0; k < 8; k++) {
          v = img_in[i*col+j+k];
          temp |= (v << (7-k));
        }
        fprintf(f, "%c", temp);
      }

      if (((i*col+j) % (col+1)) == (col)) {
        fprintf(f, "\n");
      }
    }
  }

  fclose(f);

  printf("\nPROCESS COMPLETE :)\n");


    return 0;
}
