import os
import geopandas as gpd
from shapely.geometry import Point
from whitebox.whitebox_tools import WhiteboxTools

# === 設定 ===
dem_path = "dem.tif"  # DEMファイル（GeoTIFF形式）
output_dir = "output"
os.makedirs(output_dir, exist_ok=True)

# 起点座標（緯度経度）
lat, lon = 35.3606, 138.7274  # 富士山あたりの例

# === 1. pour point をGeoJSONとして保存 ===
pour_point_path = os.path.join(output_dir, "pour_point.geojson")
gdf = gpd.GeoDataFrame(
    [{'geometry': Point(lon, lat), 'id': 0}],
    crs="EPSG:4326"
)
gdf.to_file(pour_point_path, driver="GeoJSON")

# === 2. WhiteboxTools 初期化 ===
wbt = WhiteboxTools()
wbt.set_working_dir(output_dir)

# === 3. 処理ステップ ===
# 3-1. ピットフィル処理
filled_dem = os.path.join(output_dir, "filled_dem.tif")
wbt.fill_depressions(dem_path, filled_dem)

# 3-2. 流向の計算
fdr = os.path.join(output_dir, "fdr.tif")
wbt.d8_pointer(filled_dem, fdr)

# 3-3. pour point を raster に変換（snap要）
pour_raster = os.path.join(output_dir, "pour_raster.tif")
wbt.vector_points_to_raster(
    pour_point_path, pour_raster, field="id", assign="last"
)

# 3-4. pour point を snap
snapped_pour = os.path.join(output_dir, "snapped_pour.tif")
wbt.snap_pour_points(pour_raster, filled_dem, snapped_pour, snap_dist=100)

# 3-5. 流域の抽出
watershed = os.path.join(output_dir, "watershed.tif")
wbt.watershed(fdr, snapped_pour, watershed)

# 3-6. ラスターをベクターに変換（GeoJSON）
watershed_vector = os.path.join(output_dir, "watershed.geojson")
wbt.raster_to_vector_polygons(watershed, watershed_vector)

print("✅ 集水域のGeoJSON:", watershed_vector)
