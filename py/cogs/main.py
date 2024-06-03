import discord
from discord.ext import commands
from discord import app_commands
from typing import Optional
from discord.app_commands import Choice
import csv
import jellyfish
from b30r30 import rec

LevelCount = 5
SongCount = 378
with open("./data/DB.csv",encoding="utf-8") as csvfile:
    csvread = csv.reader(csvfile)
    db = list(csvread)

def calc(rating, score):
    if(score>=10000000):
        return rating+2
    elif(score>=9800000):
        return rating+1+(score-9800000)/200000
    else:
        return rating+(score-9500000)/300000

class MyView(discord.ui.View):
    def __init__(self, score, song, diff, pc, mpc, fc, lc):
        super().__init__()
        self.score = score
        self.song = song
        self.diff = diff
        self.pc = pc
        self.mpc = mpc
        self.fc = fc
        self.lc = lc
    
    @discord.ui.button(label="Cancel", style=discord.ButtonStyle.grey, custom_id="Cancel")
    async def Cancel(self, interaction: discord.Interaction, button: discord.ui.Button):
        await interaction.response.send_message("Canceled!", ephemeral=True)
        await interaction.message.edit(view=None)
        rec(self.score, self.song, self.diff, 0, 0, self.pc, self.mpc, self.fc, self.lc)
        
    @discord.ui.button(label="Add B30", style=discord.ButtonStyle.green, custom_id="B30")
    async def B30(self, interaction: discord.Interaction, button: discord.ui.Button):
        await interaction.response.send_message("B30 record added!", ephemeral=True)
        await interaction.message.edit(view=None)
        
    @discord.ui.button(label="Add R10", style=discord.ButtonStyle.green, custom_id="R10")
    async def R10(self, interaction: discord.Interaction, button: discord.ui.Button):
        await interaction.response.send_message("R10 record added!", ephemeral=True)
        await interaction.message.edit(view=None)
        
    @discord.ui.button(label="Add B30 and R10", style=discord.ButtonStyle.blurple, custom_id="Both")
    async def Both(self, interaction: discord.Interaction, button: discord.ui.Button):
        await interaction.response.send_message("B30 and R10 record added!", ephemeral=True)
        await interaction.message.edit(view=None)

class Main(commands.Cog):
    def __init__(self, bot: commands.Bot):
        self.bot = bot

    @app_commands.command(name = "calc_by_rating", description = "Calculate Potential by Rating")
    @app_commands.describe(score = "Score", rating = "Song Rating")
    
    async def calc_by_rating(self, interaction: discord.Interaction, score: int, rating: float):
        await interaction.response.send_message(calc(rating, score))

    @app_commands.command(name = "calc_by_song", description = "Calculate Potential by Song")
    @app_commands.describe(score = "Score", song = "Song", diff = "Difficutly", pc = "Pure Count", mpc = "Max Pure Count", fc = "Far Count", lc = "Lost Count")
    @app_commands.choices(
        diff = [
            Choice(name = "PST", value = 1),
            Choice(name = "PRS", value = 2),
            Choice(name = "FTR", value = 3),
            Choice(name = "BYD", value = 4),
            Choice(name = "ETR/ETN", value = 5)
        ]
    )
    
    async def calc_by_song(self, interaction: discord.Interaction, score: int, song: str, diff: int, pc: int, mpc: int, fc: int, lc: int):
        user_id = interaction.user.id
        min_distance = float('inf')
        for num in range(0, SongCount-1):
            distance = jellyfish.levenshtein_distance(song, db[num][0])
            if(distance < min_distance):
                min_distance = distance
                songnum = num
        if(db[songnum][diff] == 0):
            await interaction.response.send_message("No Song / Difficulty found!")
        else:
            embed=discord.Embed(title="Search result", color=0x124cfd)
            embed.add_field(name="Song", value=db[songnum][0], inline=True)
            embed.add_field(name="Difficulty", value=db[0][diff], inline=True)
            embed.add_field(name="Level Potential", value=db[songnum][diff], inline=True)
            embed.add_field(name="Result", value=calc(float(db[songnum][diff]), score), inline=True)
            
            view = MyView(score, db[songnum][0], db[0][diff], pc, mpc, fc, lc)
            
            await interaction.response.send_message(embed=embed, view=view)
            
            
    
async def setup(bot: commands.Bot):
    await bot.add_cog(Main(bot))