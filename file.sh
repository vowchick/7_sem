for n in  10 100 1000 10000 100000
  do
    {
      for m in 10 100 1000 10000 100000
        do
          {
           ./first_task 1 10 1.4 0.01 $m $n
          }
      done
    }
done
