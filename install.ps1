$outdir = $args[0]
$removeguns_url = "https://github.com/mayankpatibandla/Remove-Guns/releases/download/1.0.0/removeguns-1.0.0.jar"
$unimixins_url = "https://github.com/LegacyModdingMC/UniMixins/releases/download/0.1.17/+unimixins-all-1.7.10-0.1.17.jar"

Invoke-WebRequest -Uri $removeguns_url -OutFile "$outdir\removeguns-1.0.0.jar"
Invoke-WebRequest -Uri $unimixins_url -OutFile "$outdir\unimixins-all-1.7.10-0.1.17.jar"
