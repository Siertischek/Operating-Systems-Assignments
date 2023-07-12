def main():
    p1 = 3
    p2 = 2
    p3 = 1

    inputnums = {0:0}

    line = input("Enter Input: ")

    #get only integers
    line = line.replace("<", " ")
    line = line.replace(">", " ")
    line = line.replace(",", " ")

    jobList = []

    count = 0
    time = 0
    index = 0
    #seperate and put the time/index into a dictionary
    for s in line.split():
        count = count + 1
        if count % 2 == 0:
            index = int(s)
            inputnums[time] = int(index)
            jobList.append(int(index))
        else:
            time = int(s)

    timer = 0
    owner = 0
    outputCount = 0
    jobcount = 0
    overrideCount = 0
    while True:
        timer = timer + 1

        #if the time is in the dictionary and can preempt, do so
        if timer in inputnums:
            if owner == 2 and inputnums[timer] == 1:
                print(" T2")
                outputCount = 0
                overrideCount = overrideCount + 1
                owner = inputnums[timer]
            elif owner == 3 and inputnums[timer] == 2:
                print(" T3")
                outputCount = 0
                overrideCount = overrideCount + 1
                owner = inputnums[timer]
            elif owner == 3 and inputnums[timer] == 1:
                pass
            elif owner == 2 and inputnums[timer] == 3:
                pass
            elif owner == 1 and inputnums[timer] == 3:
                pass
            elif owner == 1 and inputnums[timer] == 2:
                pass
            else:
                owner = inputnums[timer]

        #if there isn't a job running see if theres more jobs
        if owner == 0:
            if (jobcount + overrideCount) == len(jobList):
                break
            owner = jobList[jobcount+overrideCount]
        
        if owner == 1:
            #if the output has been reached reset
            if outputCount > 2:
                owner = 0
                outputCount = 0
                timer = timer - 1
                pass
            #do the initial message
            elif outputCount == 0:
                print("Time " + str(timer) + ", T1 1", end="")
                outputCount = outputCount + 1
            else:
                print("1", end="")
                outputCount = outputCount + 1
                if outputCount == 3:
                    print(" T1")
                    jobcount = jobcount + 1
        
        if owner == 2:
            if outputCount > 9:
                owner = 0
                outputCount = 0
                timer = timer - 1
                pass
            elif outputCount == 0:
                print("Time " + str(timer) + ", T2 N", end="")
                outputCount = outputCount + 1
            else:
                print("N", end="")
                outputCount = outputCount + 1
                if outputCount == 10:
                    print(" T2")
                    jobcount = jobcount + 1

        if owner == 3:
            if outputCount > 2:
                owner = 0
                outputCount = 0
                timer = timer - 1
                pass
            elif outputCount == 0:
                print("Time " + str(timer) + ", T3 3", end="")
                outputCount = outputCount + 1
            else:
                print("3", end="")
                outputCount = outputCount + 1
                if outputCount == 3:
                    print(" T3")
                    jobcount = jobcount + 1

    

if __name__ == "__main__":
    main()
