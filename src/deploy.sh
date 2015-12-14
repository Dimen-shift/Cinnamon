array=( $IPS )

make clean
#make cinnamon64-modern-INTEL
#echo "send to servers ? y/n"
#read send
#if [ "$send" != "y" ]; then
#	exit 0;
#fi
rm -fr /tmp/deploy/
UUID=$(cat /proc/sys/kernel/random/uuid)
mkdir -p /tmp/deploy/$UUID
cp -r ../src /tmp/deploy/$UUID
cd /tmp/deploy
rm -fr $UUID/src/*.o $UUID/src/gtb/Linux $UUID/src/gtb/Windows $UUID/src/gtb/OSX
tar -czf $UUID.tar.gz $UUID

for ip in "${array[@]}"
do	
	ssh geko@$ip "mkdir test" >/dev/null
	echo "scp /tmp/deploy/$UUID.tar.gz geko@$ip:test"
	scp /tmp/deploy/$UUID.tar.gz geko@$ip:test
done
exit 0
 


