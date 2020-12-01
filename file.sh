for n in 10 100 1000 10000
  do
    {
      for m in  100 1000 10000 100000
        do
          {
           ./first_task 1 10 1.4 $1 $m $n $2
          }
      done
    }
done
echo "done";
