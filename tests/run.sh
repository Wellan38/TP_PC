ps -Lf >ps.old

./test

ps -Lf >ps.new

diff ps.old ps.new>ps.diff
cat ps.diff
