# How to Get Your TeamsKeeper.exe

## 🚀 Quick Steps:

### 1. Push to GitHub
```bash
# Initialize git repo (if not already done)
git init
git add .
git commit -m "Initial TeamsKeeper release"

# Add your GitHub repo
git remote add origin https://github.com/yourusername/teamskeeper.git
git push -u origin main
```

### 2. Create a Release Tag
```bash
# Create and push a version tag
git tag v1.0.0
git push origin v1.0.0
```

### 3. Get Your .exe File
- Go to your GitHub repo
- Click "Actions" tab → Wait for build to complete (3-5 minutes)
- Click "Releases" → Download `TeamsKeeper.exe`

## 📦 Alternative: Download from Actions

If you don't want to create a release:

1. Push code to GitHub
2. Go to "Actions" tab
3. Click the latest build
4. Download "TeamsKeeper-Windows-x64-Release" artifact
5. Extract `TeamsKeeper.exe`

## 🎯 What Happens Automatically:

✅ **On every push**: Builds TeamsKeeper.exe and stores as artifact  
✅ **On version tags** (v1.0.0, v1.1.0, etc.): Creates GitHub release with .exe  
✅ **Windows 11 compatible**: Built with Visual Studio 2022  
✅ **No dependencies**: Ready-to-run executable  

## 🔧 Manual Trigger:

You can also trigger builds manually:
1. Go to Actions tab
2. Click "Build Windows Release"
3. Click "Run workflow"
4. Download the artifact when complete

## 📋 First Time Setup:

1. Create GitHub repository
2. Upload this code
3. GitHub Actions will run automatically
4. Your .exe will be ready in 3-5 minutes!

The workflow is already configured - just push your code! 🎉