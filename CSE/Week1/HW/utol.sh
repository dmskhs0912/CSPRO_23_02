echo 'working directory:'
read dirname

if [ -n "$dirname" ]
then 
	if [ ! -d "$dirname" ]
	then
		echo 'There is no such directory.'
		exit 0
	fi

	if [ ! -w "$dirname" ]
	then
		echo 'Permission Denied(w)'
		exit 0
	fi

	if [ ! -x "$dirname" ]
	then
		echo 'Permission Denied(x)'
		exit 0
	fi

	cd $dirname
fi

for dir in *
do
newname=`echo $dir | tr "[a-z] [A-Z]" "[A-Z] [a-z]"` 
mv $dir $newname
done

