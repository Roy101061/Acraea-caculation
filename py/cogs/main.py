import discord
from discord.ext import commands
from discord import app_commands
from typing import Optional
from discord.app_commands import Choice
import csv

LevelCount = 5
SongCount = 378
ppt = -1
with open("DB.csv",encoding="utf-8") as csvfile:
    csvread = csv.reader(csvfile)
    db = list(csvread)

def calc(rating, score):
    if(score>=10000000):
        ppt = rating+2
    elif(score>=9800000):
        ppt = rating+1+(score-9800000)/200000
    else:
        ppt = rating+(score-9500000)/300000

class Main(commands.Cog):
    def __init__(self, bot: commands.Bot):
        self.bot = bot

    @app_commands.command(name = "calc_by_rating", description = "Calculate Potential by Rating")
    @app_commands.describe(score = "Score", rating = "Song Rating", r10 = "Add to R10 record?")
    @app_commands.choices(
        r10 =[
            Choice(name = "YES", value = 1),
            Choice(name = "NO", value = 0)
        ]
    )
    async def calc_by_rating(self, interaction: discord.Interaction, score: int, rating: float, r10: int):
        calc(rating, score)
        await interaction.response.send_message(ppt)

    @app_commands.command(name = "calc_by_song", description = "Calculate Potential by Song")
    @app_commands.describe(score = "Score", song = "Song", diff = "Difficutly", b30 = "Add to B30 record?", r10 = "Add to R10 record?", pc = "Pure Count", mpc = "Max Pure Count", fc = "Far Count", lc = "Lost Count")
    @app_commands.choices(
        diff = [
            Choice(name = "PST", value = 1),
            Choice(name = "PRS", value = 2),
            Choice(name = "FTR", value = 3),
            Choice(name = "BYD", value = 4),
            Choice(name = "ETR/ETN", value = 5)
        ],
        b30 = [
            Choice(name = "YES", value = 1),
            Choice(name = "NO", value = 0)
        ],
        r10 =[
            Choice(name = "YES", value = 1),
            Choice(name = "NO", value = 0)
        ]
    )
    async def calc_by_song(self, interaction: discord.Interaction, score: int, song: str, diff: int, b30: int, r10: int, pc: Optional[int], mpc: Optional[int], fc: Optional[int], lc: Optional[int]):
        await interaction.response.send_message(score)

    
async def setup(bot: commands.Bot):
    await bot.add_cog(Main(bot))
