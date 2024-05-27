import os
import sqlite3

def cacu(score, song, diff, b30, r10, pc, mpc, fc, lc, id):
    FILE_PATH = './data/userdata/{id}.db'
    conn = sqlite3.connect('{FILE_PATH}')
    cur = conn.cursor()
    if not os.path.exists(FILE_PATH):
        os.makedirs(FILE_PATH)
        cur.execute("""CREATE TABLE B30 (
                        score interger,
                        song text,
                        diff interger,
                        potential real,
                        pc interger,
                        mpc interger,
                        fc interger,
                        lc interger
            )""")
        cur.execute("""CREATE TABLE R30 (
                        score interger,
                        song text,
                        diff interger,
                        potential real,
                        pc interger,
                        mpc interger,
                        fc interger,
                        lc interger,
                        count interger
            )""")
        conn.commit()
        conn.close()
    if(b30 == 1):
        chk = cur.execute("""SELECT score FROM B30 WHERE song=? AND diff=? """, (song, diff))
        if chk is None:
            cur.execute("""INSERT INTO B30 VALUES(?,?,?,?,?,?,?,?,?)""", (score, song, diff, b30, r10, pc, mpc, fc, lc))
        else:
            if(score >= chk):
                cur.execute("""UPDATE B30 SET score=?, pc=?, mpc=?, fc=?, lc=? WHERE song=? AND diff=?""", (score, pc, mpc, fc, lc, song, diff))
    if(r10 == 1):
        b=0
