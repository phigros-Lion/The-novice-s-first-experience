import tkinter as tk
from time import time

class Timecounter:
    def __init__(self):
        root = tk.Tk()
        root.title("倒计时")
        root.geometry('650x800')

        self.display = tk.Label(root, text='00:00', width=20, height=2,font=('宋体', 50), fg='red')
        self.display.pack()

        self.start_button = tk.Button(root, text='开始', width=18, height=2,font=('宋体', 20), fg='black',command=self.start)
        self.start_button.pack(pady=10)

        self.reduce_button = tk.Button(root, text='减10秒', width=20, height=2,font=('宋体', 20), fg='black',command=self.reduce)
        self.reduce_button.pack(pady=10)

        self.reset_button = tk.Button(root, text='重置', width=20, height=2,font=('宋体', 20), fg='black',command=self.reset)
        self.reset_button.pack(pady=10)

        self.reset_stop = tk.Button(root, text='暂停', width=20, height=2,font=('宋体', 20), fg='black',command=self.stop)
        self.reset_stop.pack(pady=6)

        self.named_min = tk.Label(root, text='分', width=20, height=2,font=('宋体', 20), fg='black')
        self.named_min.pack()
        self.Varmin = tk.StringVar()
        self.entrymin = tk.Entry(root, textvariable=self.Varmin)
        self.entrymin.pack(pady=3)

        self.named_sec = tk.Label(root, text='秒', width=20, height=2,font=('宋体', 20), fg='black')
        self.named_sec.pack(pady=3)
        self.Varsec = tk.StringVar()
        self.entrysec = tk.Entry(root, textvariable=self.Varsec)
        self.entrysec.pack(pady=4)

        self.btime = self.ctime = 0
        self.reduce_once = 0
        self.hold = True
        self.paused = True
        root.mainloop()

    def start(self):
        if self.paused:
            self.minsec = self.gettime()
            self.oldtime = time()
            self.paused = False
            self.run_timer()

    def reduce(self):
        self.reduce_once += 1

    def stop(self):
        if not self.paused:
            if self.hold:
                self.hold = False
                self.reset_stop.config(text='继续')
                self.btime = time()
            else:
                self.ctime = time()
                self.hold = True
                self.reset_stop.config(text='暂停')

    def reset(self):
        self.paused = True
        self.display.config(text='00:00')
        self.Varmin.set(' ')
        self.Varsec.set(' ')
        self.reduce_once = 0

    def gettime(self):
        try:
            min = self.entrymin.get()
            min = int(min)
        except:
            min = 0
        try:
            sec = self.entrysec.get()
            sec = int(sec)
        except:
            sec = 0

        self.minsec = 60 * min + sec
        return self.minsec

    def run_timer(self):
        if not self.paused:
            if self.btime and self.ctime:
                self.delta = time() - self.ctime + self.btime - self.oldtime
                self.btime = self.ctime = 0
            elif self.btime:
                self.delta = self.btime - self.oldtime
            else:
                self.delta = time() - self.oldtime

            remaining_time = max(0, self.minsec - self.delta - 10 * self.reduce_once)

            if remaining_time > 0:
                minutes,seconds= divmod(remaining_time, 60)
                deltastr = f'{int(minutes)}:{int(seconds)}'
            else:
                deltastr = '00:00'
                self.paused = True

            self.display.config(text=deltastr)
            self.display.after(1, self.run_timer)

Timecounter()
