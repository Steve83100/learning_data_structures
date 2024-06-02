from matplotlib import pyplot as pt

nums = [2,5,8,3,9,1,7,4,10,6]
labels = ['0','1','2','3','4','5','6','7','8','9']
oricolors = ['orangered','orange','gold','yellow','lawngreen','lime','springgreen','cyan','blue','blueviolet']
colors = []
for i in range(len(nums)):
    colors.append(oricolors[nums[i]-1])

pt.xlim(-1,10)
pt.ylim(0,12)
pt.bar(range(10), nums, width = 0.6, tick_label = labels, color = colors)
i = 0 # Position of arrow
pt.arrow(i, nums[i]+1.75, 0, -0.9, width=0.15, shape = 'full')
pt.show()