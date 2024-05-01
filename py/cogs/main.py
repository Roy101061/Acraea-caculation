import discord
from discord.ext import commands
from discord import app_commands
from typing import Optional
from discord.app_commands import Choice

LevelCount = 5+1
SongCount = 378 

DB = open("DB.csv")


class Main(commands.Cog):
    def __init__(self, bot: commands.Bot):
        self.bot = bot

    @app_commands.command(name = "calc", description = "Calculate Potential")
    @app_commands.describe(score = "Score", song = "Song", diff = "Difficutly", rating = "Song Rating", b30 = "Add to B30 record?", r10 = "Add to R10 record?", pc = "Pure Count", mpc = "Max Pure Count", fc = "Far Count", lc = "Lost Count")
    @app_commands.choices(
        song = [
            
        ],
        diff = [
            
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
    async def calc(self, interaction: discord.Interaction, score: int, song: Optional[str], diff: Optional[str], rating: Optional[float], b30: int, r10: int, pc: int, mpc: int, fc: int, lc: int):
        await interaction.response.send_message("Hello, world!")

async def setup(bot: commands.Bot):
    await bot.add_cog(Main(bot))
