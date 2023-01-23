#Selecionar N artistas randomicamente
#Criar um arquivo com asmusicas dos N artistas selecionados

artists="artists_full.csv"
tracks="tracks_full.csv"

#Numero de artistas
N=300000
#Seleciona N artista aleatorios
shuf -n$N $artists > "artists_$N.csv"

#Coletar as ultmas N linhas (parece ser artistas mais populares)
#tail -n $N  $artists > "artists_$N.csv"

#como há muitos artistas sem musicas, contabilizar apenas os artistas com musicas
num=0
while IFS= read -r line
do 
   a=`echo $line | awk -F ';' '{print $1}'`
   #echo $a
   tr=$(cat $tracks | grep  $a)
   if [ ! -z "$tr" ]
   then 
   	echo $tr  >> "tracks_$N.csv"
   	num=$(($num +1))
    echo $num 
   	echo $line  >> "artists_temp.csv"
   fi
   
done <  "artists_$N.csv"

rm "artists_$N.csv"
mv "artists_temp.csv"  "artists_$num.csv"
mv "tracks_$N.csv"  "tracks_$num.csv"