# truncate it
 echo '' > hosts_up;

# pega os hosts da profa
 wget http://www2.ic.uff.br/~simone/labprogparal/lab1/hostsname;

# see who's up and running
 for f in `cat hostsname`;
     do
   echo "$f";
        ssh lab@"$f" uptime && echo "$f">> hosts_up;
         #ping -c 1 "$f" -W1 && ssh lab@"$f" uptime && echo "$f">> hosts_up;
     done;

# outgoing
mkdir -p  ~/dist;
 
# compile, distribute and run
mpicc mpi_bandwidth.c -o band.a \
  && cp band.a ~/dist/boladao.out \
  && (
    for host in `cat hosts_up`;
      do
        echo $host;
        scp -r ~/dist $host:~/;
      done
    ) \
  #&& mpirun --hostfile hosts_up -np 2 -mca plm_rsh_no_tree_spawn 1  ~/dist/boladao.out