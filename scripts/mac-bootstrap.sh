if ["$GIT_URL" = ""] then
  echo "Please enter the remote git URL (https://github.com/[username]/[repo-name].git):"
  read GIT_URL
fi
if ["$GIT_URL" = ""] then
  echo "GIT_URL empty, quitting."
  exit 1
fi
git init
git remote add origin $GIT_URL
git pull origin master
