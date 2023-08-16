# Copyright (C) 2020-2023 CERN and UCLouvain.
# Licensed under the GNU Lesser General Public License (version 3 or later).
# Created by: A. Valassi (Aug 2023) for the MG5aMC CUDACPP plugin.

The following describes how the initial import of the CUDACPP plugin was done from madgraph4gpu.

1. CREATE A NEW REPO FOR MG5AMCNLO_CUDACPP

Create a new repo on github.
Then switch to the command line.

# Prepare a new empty directory for the mg5amcnlo_cudacpp project.
# Edit a README.md file
mkdir -p /data/avalassi/GPU2023/CUDACPP/mg5amcnlo_cudacpp
cd /data/avalassi/GPU2023/CUDACPP/mg5amcnlo_cudacpp
nano README.md

# Initialise the directory as a git directory and commit the README.md file.
git init
git add README.md
git commit -a
git branch -M master
git remote add origin https://github.com/mg5amcnlo/mg5amcnlo_cudacpp.git
git push -u origin master

2. FILTER OUT THE CUDACPP PLUGIN FROM THE MADGRAPH4GPU REPO AS BRANCH "PLUGIN"

# Go to my clone of my madgraph4gpu fork on gitlab
cd /data/avalassi/GPU2023/madgraph4gpuMOD
git remote -v
  origin          https://:@gitlab.cern.ch:8443/valassi/madgraph4gpu.git (fetch)
  origin          https://:@gitlab.cern.ch:8443/valassi/madgraph4gpu.git (push)
  upstream        https://github.com/madgraph5/madgraph4gpu.git (fetch)
  upstream        https://github.com/madgraph5/madgraph4gpu.git (push)

# Create and push a new branch plugin in my madgraph4gpu fork from the latest upstream/master
# Note down what was the last commit hash at the time
git fetch master
git checkout -b plugin upstream/master
git push origin -u plugin
git log --oneline -n1 | awk '{print $1}'
  fe3cdf769

# Filter out only the plugin files and move them to the top directory
# Force push to branch plugin in my madgraph4gpu fork
git filter-branch -f --subdirectory-filter epochX/cudacpp/CODEGEN/PLUGIN/CUDACPP_SA_OUTPUT/
git status
  ...
  On branch plugin
  Your branch and 'origin/plugin' have diverged,
  and have 831 and 8041 different commits each, respectively.
git push -f

# Rewrite the commit messages in branch plugin to create links to madgraph4gpu issues
# Force push to branch plugin in my madgraph4gpu fork
git filter-branch -f --msg-filter 'sed -r "s,( |\()#([0-9]),\1madgraph5/madgraph4gpu#\2,g"'
git push -f

3. COMMIT THE MADGRAPH4GPU "PLUGIN" BRANCH TO MY FORK OF THE MG5AMCNLO_CUDACPP REPO

# Go to my clone of the mg5amcnlo_cudacpp repo on github
# This contains a remote of my fork for mg5amcnlo_cudacpp on github
# It also contains a remote of my fork for madgraph4gpu on gitlab
cd /data/avalassi/GPU2023/CUDACPP/mg5amcnlo_cudacpp
git remote -v
  glav    https://:@gitlab.cern.ch:8443/valassi/madgraph4gpu.git (fetch)
  glav    https://:@gitlab.cern.ch:8443/valassi/madgraph4gpu.git (push)
  origin  https://github.com/mg5amcnlo/mg5amcnlo_cudacpp.git (fetch)
  origin  https://github.com/mg5amcnlo/mg5amcnlo_cudacpp.git (push)
  valassi https://github.com/valassi/mg5amcnlo_cudacpp.git (fetch)
  valassi https://github.com/valassi/mg5amcnlo_cudacpp.git (push)

# Checkout (in this mg5amcnlo_cudacpp repo clone) the plugin branch (from the unrelated madgraph4gpu repo)
git checkout -b cudacpp_plugin glav/plugin
git push valassi -u cudacpp_plugin

# Merge the initial mg5amcnlo_cudacpp commit (with README.md) from origin/master onto this branch
# The branch can now be merged onto origin/master: open a MR on github
git merge origin/master --allow-unrelated-histories
