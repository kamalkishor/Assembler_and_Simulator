			/* -------------------------------------------- */
			/* instruction set simulator.  			*/
			/* fetch instruction , decode it , execute it.  */
			/* using 2 registers and one memory location.	*/
			/* r1,r2 -> register.				*/
			/* m -> memory.					*/
			/* Garvit Sharma - y10uc112.			*/
			/* Kamal Kishor Sharma - y10uc139.		*/
			/* Date 15 sep 2011.				*/  
			/* -------------------------------------------- */

#include<stdio.h>
#include<string.h>

main()
{
	FILE *fs,*fd;

	int i=0,s,j=0,k,t,num=0,num1=0,r1,r2,m,flag=1,mem;		
	char op[10],re1[5],re2[5];
	char operation[12][10]={"add","sub","mul","store","move","load","loadi","inc","dec","jump","out","halt"};
	char hex[12][5]={"0x01","0x21","0x41","0x68","0x81","0xa1","0xc3","0xe3","0xeb","0xf3","0xf7","0xff"};
        char c,inst[100][100];

	fd=fopen("b.txt","r");

	rewind(fd);

	while((c=fgetc(fd))!=EOF)
	{
		if(c!='\n')
		inst[i][j++]=c;
		else
		{
			inst[i][j]='\0';
			i++; j=0;
		}
	}
l1:
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

		if(flag==0 && mem==atoi(op))	
		flag=1;

		if(flag==1)
		{
			for(k=0;k<12;k++)
			if(strcmp(re1,hex[k])==0)
			break;
		
			switch(k)
			{
			case 0: r1=r1+r2;
				break;		
			case 1: r1=r1-r2;
				break;		
			case 2: r1=r1*r2;
				break;		
			case 3: m=r1;
				break;		
			case 4: r2=r1;
				break;		
			case 5: r2=m;
				break;		
			case 6: r1=atoi(re2);
				break;		
			case 7: r1=r1+1;
				break;		
			case 8: r1=r1-1;
				break;		
			case 9: flag=0;
				mem=atoi(re2);
				goto l1;
				break;		
			case 10: printf("%d\n",r1);
				break;		
			case 11:goto l;
				break;		
			}

		}

	}	
		    
l:
	fclose(fd);
}
