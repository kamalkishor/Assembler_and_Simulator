			/* -------------------------------------------- */
			/* Assembler based on my ISA			*/
			/* r1,r2 -> register				*/
			/* m -> memory					*/
			/* 1) add   -> r1=r1+r2				*/
			/* 2) sub   -> r1=r1-r2				*/
			/* 3) mul   -> r1=r1*r2				*/
			/* 4) store -> m=r1				*/
			/* 5) move  -> r2=r1				*/
			/* 6) load  -> r2=m				*/
			/* 7) loadi -> r1=value				*/
			/* 8) inc   -> r1=r1+1				*/
			/* 9) dec   -> r1=r1-1				*/
			/* 10)jump  -> jump to specefic inst. location	*/
			/* 11)out   -> print r1				*/
			/* 12)halt  -> end of execution.		*/ 
			/* Garvit Sharma - y10uc112.			*/
			/* Kamal Kishor Sharma - y10uc139.		*/
			/* Date 15 sep 2011.				*/  
			/* -------------------------------------------- */

#include<stdio.h>
#include<string.h>

int po(int k)
{
	int i,temp=1;
	for(i=0;i<3-k;i++)
	temp=temp*2;
return temp;
}

main()
{
	FILE *fs,*fd;

	int i=0,s,j=0,k,t,num=0,num1=0;		

	char op[10],re1[5],re2[5];

	char operation[12][10]={"add","sub","mul","store","move","load","loadi","inc","dec","jump","out","halt"};

	char opcode[12][10]={"00000001","00100001","01000001","01101000","10000001","10100001","11000011","11100011","11101011","11110011","11110111","11111111"};

        char c,alp[16][3]={"","","","","","","","","","","a","b","c","d","e","f"},inst[100][100];

	fs=fopen("a.txt","r");

	fd=fopen("b.txt","w");
  
	rewind(fs);

	while((c=fgetc(fs))!=EOF)
	{
		if(c!='\n')
		inst[i][j++]=c;
		else
		{
			inst[i][j]='\0';
			i++; j=0;
		}
	}

	for(j=0;j<i;j++)
	{

		op[0]='\0';
		re1[0]='\0';
		re2[0]='\0';
		s=0;
		num=0;
		num1=0;

		for(k=0;inst[j][k]!='\0' && inst[j][k]!=' ';k++)
	      	op[s++]=inst[j][k];
	      	op[s]='\0';
	      	s=0; k++;

		for(;inst[j][k]!='\0' && inst[j][k]!=' ';k++)
		re1[s++]=inst[j][k];
		re1[s]='\0';
		s=0; k++;

		for(;inst[j][k]!='\0' && inst[j][k]!=' ';k++)
		re2[s++]=inst[j][k];
		re2[s]='\0';

		for(k=0;k<12;k++)
		if(strcmp(op,operation[k])==0)
		break;
		
			if(k==11)
			{fprintf(fd,"%03d 0xff\n",k); break;}
			else
			{
				for(t=0;t<4;t++)
				num=num+po(t)*(opcode[k][t]-'0');
				for(t=4;t<8;t++)
				num1=num1+po(t-4)*(opcode[k][t]-'0');		
				if((num>=0 && num<10) && (num1>=0 && num1<10))				
				{ fprintf(fd,"%03d 0x%d%d",k,num,num1);}
				
				if((num>=0 && num<10) && num1>=10)				
				fprintf(fd,"%03d 0x%d%s",k,num,alp[num1]);
				
				if(num>=10 && (num1>=0 && num1<10))				
				{ fprintf(fd,"%03d 0x%s%d",k,alp[num],num1);}
				
				if(num>=10 && num1>=10)				
				fprintf(fd,"%03d 0x%s%s",k,alp[num],alp[num1]);

				if(strcmp(op,"loadi")==0)
				fprintf(fd," %s\n",re2);
				else if(strcmp(op,"jump")==0)
				fprintf(fd," %s\n",re1);
				else
				fprintf(fd,"\n");
			}
	}	
		    

	fclose(fd);
	fclose(fs);
}
