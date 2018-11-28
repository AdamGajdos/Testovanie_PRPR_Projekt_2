#include <stdio.h>			// a,h zmen na strcmp    // z je strstr
#include <stdlib.h>			// prerob inituj tak, aby si mal strcpy(akt->polozka,nacitaj_str_s(f) a pod.
#include <string.h>
#include <ctype.h>

typedef struct prvok
{
	char kategoria[51];
	char znacka[51];
	char predajca[101];
	int  cena;
	int  rok_vyroby;
	char stav_vozidla[201];
	struct prvok *dalsi;
} PRVOK;

int pocet_zaznamov(FILE *f)							// nechaj
{
	int  pocet=0;
	char riadok[256];
	
	f=fopen("auta.txt","r");
	if (f != NULL)
	{
		while (fgets(riadok,sizeof(riadok),f)!=NULL)
		 {
		 	if (riadok[0]=='$')
			 pocet++;  
		 }
	}
	fclose(f);
	return pocet;	
}

void vypis_prvok(PRVOK *aky,int poradie)			// aky prvok treba vypisat
{
	printf("%d.\n",poradie);
	printf("kategoria: %s\n",aky->kategoria);
	printf("znacka: %s\n",aky->znacka);
	printf("predajca: %s\n",aky->predajca);
	printf("cena %d\n",aky->cena);
	printf("rok_vyroby: %d\n",aky->rok_vyroby);
	printf("stav: %s\n",aky->stav_vozidla);
}

void daj_na_male(char *vstup)
{
	int i=0;
	while(vstup[i])
	{
		vstup[i]=tolower(vstup[i]);
		i++;
	}	
}

PRVOK *novy_zaznam_s(FILE *f)					// nacitanie noveho zaznamu zo suboru
{
	PRVOK *novy;
	char pom_kateg[51];
	char pom_znac[51];
	char pom_predaj[101];
	int  pom_cena;
	int  pom_rok_vyroby;
	char pom_stav[201];
	char znak;
	
	novy=(PRVOK*)malloc(sizeof(PRVOK));
	
	znak=fgetc(f);											// nacitanie dolaru
	znak=fgetc(f);											// nacitanie entru
			
	fscanf(f,"%[^\n]",pom_kateg);
	znak=fgetc(f);											// odobranie '\n'
	
	fscanf(f,"%[^\n]",pom_znac);
	znak=fgetc(f);
	
	fscanf(f,"%[^\n]",pom_predaj);
	znak=fgetc(f);
	
	fscanf(f,"%d",&pom_cena);
	fscanf(f,"%d",&pom_rok_vyroby);
	
	fscanf(f,"%[^\n]",pom_stav);
	znak=fgetc(f);

	strcpy(novy->kategoria,pom_kateg);			
	strcpy(novy->znacka,pom_znac);			
	strcpy(novy->predajca,pom_predaj);
	novy->cena=pom_cena;			
	novy->rok_vyroby=pom_rok_vyroby;
	strcpy(novy->stav_vozidla,pom_stav);
	novy->dalsi=NULL;
	return novy;
}

PRVOK *novy_zaznam_k() 							// nacitanie noveho zaznamu z klavesnice
{

	char pom_kateg[51];
	char pom_znac[51];
	char pom_predaj[101];
	int  pom_cena;
	int  pom_rok_vyroby;
	char pom_stav[201];
	PRVOK *novy;
	char znak;
	
	novy=(PRVOK*)malloc(sizeof(PRVOK));

	
	scanf("%[^\n]",pom_kateg);
	znak=getchar();						// odobranie '\n'
	
	scanf("%[^\n]",pom_znac);
	znak=getchar();
	
	scanf("%[^\n]",pom_predaj);
	znak=getchar();
	
	scanf("%d",&pom_cena);
	scanf("%d",&pom_rok_vyroby);
	
	scanf("%[^\n]",pom_stav);
	znak=getchar();
		
		
	strcpy(novy->kategoria,pom_kateg);			
	strcpy(novy->znacka,pom_znac);			
	strcpy(novy->predajca,pom_predaj);
	strcpy(novy->stav_vozidla,pom_stav);
	novy->cena=pom_cena;			
	novy->rok_vyroby=pom_rok_vyroby;
	novy->dalsi=NULL;
	
	return novy;
}

void funkcia_pridaj(PRVOK **zaciatok)  	 		// funkcia p
{
	PRVOK 	*akt,*novy;
	int 	k,pocet,i=1;
	FILE 	*f;
	
	pocet=pocet_zaznamov(f);
	scanf("%d",&k);
	
	if (k<pocet)
	 {
	 	akt=*zaciatok;
	 	while(i<k-1)		// posun na poziciu kedy dalsi prvok je prvok na pozicii, na ktoru chcem vlozit novy prvok
	 	 akt=akt->dalsi;
	 	
	 	novy=novy_zaznam_k();
	 	novy->dalsi=akt->dalsi;
	 	akt->dalsi=novy;
	 	
	 }
	 
	else
	{
		akt=*zaciatok;
		while(akt->dalsi != NULL) 		// som na poslednom prvku
		 akt=akt->dalsi;
		
		novy=novy_zaznam_k();			// nacitanie noveho zaznamu z klavesnice
		akt->dalsi=novy; 			// pridanie noveho  zaznamu na koniec zoznamu
	 } 
	
}

void funkcia_hladaj(PRVOK *zaciatok)			// funkcia h	ide
{
	char  kluc[51];
	char  vzor[51];
	char  znak;
	PRVOK *akt;
	int   pom_cena,poradie=1;	
	
	scanf("%[^\n]",kluc);
	znak=getchar();				// odobranie '\n'
	
	daj_na_male(kluc);
	
	scanf("%d",&pom_cena);
	
	akt=zaciatok;
	while (akt!=NULL)
	{
		strcpy(vzor,akt->znacka);
		
		daj_na_male(vzor);
			
		if ((strcmp(vzor,kluc)==0) && (akt->cena <= pom_cena))
		{
			vypis_prvok(akt,poradie);
			poradie++;
		}
		akt=akt->dalsi;
	}
 if(poradie == 1)
  printf("V ponuke nie su pozadovane auta.\n");
	
}

void funkcia_aktualizuj(PRVOK **zaciatok)		// funkcia a
{
	int pocet_aktualizacii=0;
	char  kluc[51];
	char  vzor[51];
	PRVOK *akt;
	int   pom_rok;
	char  znak;
	
	scanf("%[^\n]",kluc);
	znak=getchar();				// odobranie '\n'
	daj_na_male(kluc);
	
	scanf("%d",&pom_rok);
	
	akt=*zaciatok;
	while (akt!=NULL)
	{
		strcpy(vzor,akt->znacka);
		daj_na_male(vzor);
		
		if ((strcmp(vzor,kluc)==0) && (akt->rok_vyroby == pom_rok))		// ak sa jedna o auto danej znacky so zadanym rokom vyroby
		{
			if ((akt->cena - 100)<0)
			 akt->cena=0;
			else 
			 akt->cena-=100; 
			pocet_aktualizacii++;
		}
		akt=akt->dalsi;
	}
	
 printf("Aktualizovalo sa %d zaznamov\n",pocet_aktualizacii);	
}

void funkcia_uvolni(PRVOK **zaciatok)			// funkcia k	ide
{
	PRVOK *pom;
	while ((*zaciatok)->dalsi != NULL)
	 {
	 	pom=*zaciatok;
	 	*zaciatok=(*zaciatok)->dalsi;
	 	free(pom);
	 	pom=NULL;
	 }
	 free(*zaciatok);
	 *zaciatok=NULL;
}

int vytvor(PRVOK **zac)							// funkcia n	ide
{
	PRVOK   *akt;
	char    slovo[51];
	int     i,cislo1,cislo2;		 
	FILE 	*f;
	
	int pocet;
	pocet=pocet_zaznamov(f);
	
	f=fopen("auta.txt","r");	
	
	*zac=(PRVOK*)malloc(sizeof(PRVOK));
	akt=*zac;
	for (i=1;i<=pocet;i++)
{
		
	fgetc(f);								// odobratie '$'
	fgetc(f);								// odobratie '\n'
	
	fscanf(f,"%[^\n]",slovo);				// nacitanie kategorie
	 fgetc(f);								// odobratie '\n'
	strcpy(akt->kategoria,slovo);			// priradenie do zaznamu
	
	fscanf(f,"%[^\n]",slovo);				// nacitanie znacky
	 fgetc(f);								// odobratie '\n'
	strcpy(akt->znacka,slovo);				// priradenie do zaznamu
	
	fscanf(f,"%[^\n]",slovo);				// nacitanie predajcu
	 fgetc(f);								// odobratie '\n'
	strcpy(akt->predajca,slovo);			// priradenie do zaznamu
	
	fscanf(f,"%d %d",&cislo1,&cislo2);		// nacitanie ceny a roku vyroby
	 fgetc(f);								// odobratie '\n'
	 akt->cena=cislo1;						// priradenie do zaznamu
	 akt->rok_vyroby=cislo2;				// priradenie do zaznamu

	fscanf(f,"%[^\n]",slovo);				// nacitanie stavu vozidla
	 fgetc(f);								// odobratie '\n'
	strcpy(akt->stav_vozidla,slovo);		// priradenie do zaznamu
	
	akt->dalsi=(PRVOK*)malloc(sizeof(PRVOK));	// alokovanie dalsieho zaznamu
	akt=akt->dalsi;								// posun na novo vytvoreny prvok
}
	akt->dalsi=NULL;							// posledny zaznam ukazuje na NULL
		
	fclose(f);

return pocet;
}

int funkcia_zmaz(PRVOK **zaciatok)				// funkcia z	ide
{
	int  	pocet_zmazanych=0;
	int  	i;
	char 	kluc[51];
	char 	vzor[51];		// vyberam vzdy zo znacky zo zaznamu v zozname
	PRVOK 	*pom,*akt;
	char    znak;
	
	scanf("%[^\n]",kluc);
	znak=getchar();				// odobranie '\n'
	daj_na_male(kluc);
								/* prejdenie spojoveho zoznamu a odstranenie zaznamov podla kluca. Ak bol zaciatocny prvok vyhovujuci tak ho zatial vynechame */
	    akt=*zaciatok;
		while(akt->dalsi!=NULL)
		 {  
		 	strcpy(vzor,akt->dalsi->znacka);
		 	daj_na_male(vzor);
		 
			if (strstr(vzor,kluc) != NULL)	 
		    {
			 pom=akt->dalsi;
		     akt->dalsi=pom->dalsi;
		     free(pom);
		     pom=NULL;
		     pocet_zmazanych++;
		     akt=*zaciatok;
		     continue;
				// ak zmazem nejaky zaznam, tak sa vratim na zaciatok a zacnem tak poleprechadzat od zaciatku
			}
			
			akt=akt->dalsi;
		}
	strcpy(vzor,(*zaciatok)->znacka);	 
	daj_na_male(vzor);
	if (strstr(vzor,kluc)!= NULL)		/* odstranenie zaciatocneho prvku ak vyhovuje klucu */
	 {
	 	 pom=*zaciatok;
		 *zaciatok=(*zaciatok)->dalsi;
		 free(pom);
		 pom=NULL;
		 pocet_zmazanych++;
	}
	
return pocet_zmazanych;	
}

void funkcia_vypis(PRVOK *zaciatok)				// funkcia v	ide
{
	PRVOK *akt;
	int poradie=1;
	
	akt=zaciatok;
	
	while(akt->dalsi != NULL)
	{
		vypis_prvok(akt,poradie);
		poradie++;
		akt=akt->dalsi;
	}
}

int main() 
{
	FILE *f;
	PRVOK *zaciatok=NULL;
	char operacia;
	int vytvoreny_spojak=0,pocet,pocetzmaz=0;
	char pom[51],znak;
	
	pocet=vytvor(&zaciatok);
	pocetzmaz=funkcia_zmaz(&zaciatok);
	printf("ZMAZALO sa %d\n",pocetzmaz);
	funkcia_vypis(zaciatok);
	return 0;
}
